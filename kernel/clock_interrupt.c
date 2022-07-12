#include "clock_interrupt.h"

uint8_t ticks = 0;


void timer_int_func(void* x)
{
    __asm__ volatile ("cli");
    __asm__ volatile ("in al, 0x60"); //read information from the device
    __asm__ volatile ("mov al, 0x20");
    __asm__ volatile ("out 0x20, al"); //tell the PIC its over

    //locals
    uint32_t last_eax;
    uint32_t last_edx;
    uint32_t last_ecx;

    //arguments
    uint32_t last_ebp;
    uint32_t last_eip;
    uint32_t last_cs;
    uint32_t last_eflags;
    uint32_t last_esp;
    uint32_t last_ss;


    if(ticks++ == 20)
    {
        ticks = 0; // reset watcher

        //locals ( pushed inside the function itself the registers of last task ). getting POP-ed at the end.
        __asm__ volatile ("mov %0, [ebp-0x0c]":"=r" (last_eax)); // ebp-0x0c - the eax of last function
        __asm__ volatile ("mov %0, [ebp-0x08]":"=r" (last_edx)); // ebp-0x08 - the edx of last function
        __asm__ volatile ("mov %0, [ebp-0x04]":"=r" (last_ecx)); // ebp-0x04 - the ecx of last function

        //the ebp - also pushed by the function itself. getting POP-ed at the end.
        __asm__ volatile ("mov %0, [ebp+0x00]":"=r" (last_ebp)); // ebp+0x00 - the ebp of last function

        //arguments - seems like the hardware itself push the rest
        __asm__ volatile ("mov %0, [ebp+0x04]":"=r" (last_eip)); // ebp+0x04 - the eip of last function
        __asm__ volatile ("mov %0, [ebp+0x08]":"=r" (last_cs)); // ebp+0x08 - the cs of last function
        __asm__ volatile ("mov %0, [ebp+0x0c]":"=r" (last_eflags)); // ebp+0x0c - eflags of last function
        __asm__ volatile ("mov %0, [ebp+0x10]":"=r" (last_esp)); // ebp+0x10 - the esp of last function
        __asm__ volatile ("mov %0, [ebp+0x14]":"=r" (last_ss)); // ebp+0x14 - the cs of last function

        //save register information for the task that stopped running
        tasks[currently_running_task_id].ebp = (uint32_t)last_ebp;
        tasks[currently_running_task_id].eip = (uint32_t)last_eip;
        tasks[currently_running_task_id].esp = (uint32_t)last_esp;
        tasks[currently_running_task_id].eflags = (uint32_t)last_eflags;
        tasks[currently_running_task_id].eax = (uint32_t)last_eax;
        tasks[currently_running_task_id].ecx = (uint32_t)last_ecx;
        tasks[currently_running_task_id].edx = (uint32_t)last_edx;



        scheduler(); // updating the current_running_task_id to point to the new chosen task

        //put the appropriate information on the task so iret will schedule next task rpoperly.
        __asm__ volatile ("mov ax, 0x23");	// user mode data selector is 0x20 (GDT entry 3). Also sets RPL to 3
        __asm__ volatile ("mov ds, ax");
        __asm__ volatile ("mov es, ax");
        __asm__ volatile ("mov fs, ax");
        __asm__ volatile ("mov gs, ax");
        __asm__ volatile ("mov [ebp-0x0c], %0"::"r" (tasks[currently_running_task_id].eax)); // ebp-0x0c - the eax of chosen task
        __asm__ volatile ("mov [ebp-0x08], %0"::"r" (tasks[currently_running_task_id].ecx)); // ebp-0x08 - the edx of chosen task
        __asm__ volatile ("mov [ebp-0x04], %0"::"r" (tasks[currently_running_task_id].edx)); // ebp-0x04 - the ecx of chosen task
        __asm__ volatile ("mov [ebp+0x00], %0"::"r" (tasks[currently_running_task_id].ebp)); // ebp+0x00 - the ebp of chosen task
        __asm__ volatile ("mov [ebp+0x04], %0"::"r" (tasks[currently_running_task_id].eip)); // ebp+0x04 - the eip of chosen task
        __asm__ volatile ("mov [ebp+0x0c], %0"::"r" (tasks[currently_running_task_id].eflags)); // ebp+0x0c - the eflags of chosen task
        __asm__ volatile ("mov [ebp+0x10], %0"::"r" (tasks[currently_running_task_id].esp)); // ebp + 0x10 - the esp of chosen task
        //the eax,ecx,edx and ebp all POP-ed by order, the rest we get from the iret OP.
    }
}