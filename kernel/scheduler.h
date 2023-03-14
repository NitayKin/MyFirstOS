#ifndef scheduler_header
#define scheduler_header
#include "print.h"
#include "tasks.h"
#include "auxility.h"

void scheduler(void);

/*
this is in a big define because we are playing with the esp and ebp in order to change the registers when returning from the interrupt (in order to
return from the interrupt with the next scheduled task registers).
first we are saving the current registers, and then calling the scheduler in order to find the next task to run.
afterwards, we take the saved registered of the chosen task to run, and put them in the stack in order to pop them when returning from the interrupt rutine.
*/
#define context_switch() \
uint32_t last_ebx; \
uint32_t last_eax; \
uint32_t last_edx; \
uint32_t last_ecx; \
uint32_t last_ebp; \
uint32_t last_eip; \
uint32_t last_eflags; \
uint32_t last_esp; \
__asm__ volatile ("mov %0, ebx":"=r" (last_ebx)); \
__asm__ volatile ("mov %0, eax":"=r" (last_eax)); \
__asm__ volatile ("mov %0, edx":"=r" (last_edx)); \
__asm__ volatile ("mov %0, ecx":"=r" (last_ecx)); \
__asm__ volatile ("mov %0, [ebp+0x00]":"=r" (last_ebp)); \
__asm__ volatile ("mov %0, [ebp+0x04]":"=r" (last_eip)); \
__asm__ volatile ("mov %0, [ebp+0x0c]":"=r" (last_eflags)); \
__asm__ volatile ("mov %0, [ebp+0x10]":"=r" (last_esp)); \
tasks[currently_running_task_id].eax = (uint32_t)last_eax; \
tasks[currently_running_task_id].ebx = (uint32_t)last_ebx; \
tasks[currently_running_task_id].ecx = (uint32_t)last_ecx; \
tasks[currently_running_task_id].edx = (uint32_t)last_edx; \
tasks[currently_running_task_id].ebp = (uint32_t)last_ebp; \
tasks[currently_running_task_id].eip = (uint32_t)last_eip; \
tasks[currently_running_task_id].esp = (uint32_t)last_esp; \
tasks[currently_running_task_id].eflags = (uint32_t)last_eflags; \
if (currently_running_task_id == 0){ \
	tasks[currently_running_task_id].status = alive; \
	tasks[currently_running_task_id].id = KERNEL_TASK_CODE; \
} \
scheduler(); \
__asm__ volatile ("mov eax, %0"::"r" (tasks[currently_running_task_id].eax)); \
__asm__ volatile ("mov ebx, %0"::"r" (tasks[currently_running_task_id].ebx)); \
__asm__ volatile ("mov ecx, %0"::"r" (tasks[currently_running_task_id].edx)); \
__asm__ volatile ("mov edx, %0"::"r" (tasks[currently_running_task_id].ecx)); \
__asm__ volatile ("mov [ebp+0x00], %0"::"r" (tasks[currently_running_task_id].ebp)); \
__asm__ volatile ("mov [ebp+0x04], %0"::"r" (tasks[currently_running_task_id].eip)); \
__asm__ volatile ("mov [ebp+0x0c], %0"::"r" (tasks[currently_running_task_id].eflags)); \
__asm__ volatile ("mov [ebp+0x10], %0"::"r" (tasks[currently_running_task_id].esp));



#endif
