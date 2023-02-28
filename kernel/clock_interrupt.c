#include "clock_interrupt.h"

uint8_t ticks = 0;


void timer_int_func(void* x)
{
    __asm__ volatile ("cli");
    __asm__ volatile ("in al, 0x60"); //read information from the device
    __asm__ volatile ("mov al, 0x20");
    __asm__ volatile ("out 0x20, al"); //tell the PIC its over

    //ebx for some reason needs special treatment
    uint32_t last_ebx;

    //locals
    uint32_t last_eax;
    uint32_t last_edx;
    uint32_t last_ecx;

    //arguments
    uint32_t last_ebp;
    uint32_t last_eip;
    uint32_t last_eflags;
    uint32_t last_esp;


    if(ticks++ == 20)
    {
        ticks = 0; // reset watcher

        //save general registers
        __asm__ volatile ("mov %0, ebx":"=r" (last_ebx));
        __asm__ volatile ("mov %0, eax":"=r" (last_eax));
        __asm__ volatile ("mov %0, edx":"=r" (last_edx));
        __asm__ volatile ("mov %0, ecx":"=r" (last_ecx));

        //the ebp - also pushed by the function itself. getting POP-ed at the end.
        __asm__ volatile ("mov %0, [ebp+0x00]":"=r" (last_ebp)); // ebp+0x00 - the ebp of last function

        //arguments - the hardware itself push the rest
        __asm__ volatile ("mov %0, [ebp+0x04]":"=r" (last_eip)); // ebp+0x04 - the eip of last function
        __asm__ volatile ("mov %0, [ebp+0x0c]":"=r" (last_eflags)); // ebp+0x0c - eflags of last function
        __asm__ volatile ("mov %0, [ebp+0x10]":"=r" (last_esp)); // ebp+0x10 - the esp of last function

        //save register information for the task that stopped running
        tasks[currently_running_task_id].eax = (uint32_t)last_eax;
        tasks[currently_running_task_id].ebx = (uint32_t)last_ebx;
        tasks[currently_running_task_id].ecx = (uint32_t)last_ecx;
        tasks[currently_running_task_id].edx = (uint32_t)last_edx;

        tasks[currently_running_task_id].ebp = (uint32_t)last_ebp;
        tasks[currently_running_task_id].eip = (uint32_t)last_eip;
        tasks[currently_running_task_id].esp = (uint32_t)last_esp;
        tasks[currently_running_task_id].eflags = (uint32_t)last_eflags;

        if (currently_running_task_id == 0){ // kernel task - always keep alive
			tasks[currently_running_task_id].status = alive;
			tasks[currently_running_task_id].id = KERNEL_TASK_CODE;
        }

        scheduler(); // updating the current_running_task_id to point to the new chosen task

        __asm__ volatile ("mov eax, %0"::"r" (tasks[currently_running_task_id].eax)); // load the eax of chosen task
        __asm__ volatile ("mov ebx, %0"::"r" (tasks[currently_running_task_id].ebx)); // load the ebx of chosen task
        __asm__ volatile ("mov ecx, %0"::"r" (tasks[currently_running_task_id].edx)); // load the ecx of chosen task
        __asm__ volatile ("mov edx, %0"::"r" (tasks[currently_running_task_id].ecx)); // load the edx of chosen task
        __asm__ volatile ("mov [ebp+0x00], %0"::"r" (tasks[currently_running_task_id].ebp)); // ebp+0x00 - the ebp of chosen task
        __asm__ volatile ("mov [ebp+0x04], %0"::"r" (tasks[currently_running_task_id].eip)); // ebp+0x04 - the eip of chosen task
        __asm__ volatile ("mov [ebp+0x0c], %0"::"r" (tasks[currently_running_task_id].eflags)); // ebp+0x0c - the eflags of chosen task
        __asm__ volatile ("mov [ebp+0x10], %0"::"r" (tasks[currently_running_task_id].esp)); // ebp + 0x10 - the esp of chosen task
        //the eax,ecx,edx and ebp all POP-ed by order, the rest we get from the iret OP.
        
    }
}
