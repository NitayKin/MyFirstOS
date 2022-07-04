#include "scheduler.h"

void scheduler()
{
    if (total_tasks > 0)
    {
        TaskDescription task_to_schedule = {1,1,1,1};
        TaskDescription* task_to_schedule_p= &task_to_schedule;
        for(int i=0;i<256;++i) // search for the next task to run
        {
            if( (tasks[i].id != currently_running_task_id) && (tasks[i].alive==true))
            {
                get_task_by_id(task_to_schedule_p,tasks[i].id);
                currently_running_task_id = tasks[i].id;
                break;
            }
        }
        __asm__ volatile ("mov ax, 0x23 \n\t"
        "mov ds, ax \n\t"
        "mov es, ax \n\t"
        "mov fs, ax \n\t"
        "mov gs, ax \n\t"
        "push 0x23 \n\t"
        "push %0 \n\t"
        "pushfd \n\t"
        "pop eax \n\t"
        "or eax, 0x200 \n\t"
        "push eax \n\t"
        "push 0x1b \n\t"
        "mov eax, %1 \n\t"
        "push eax \n\t"
        "iretd"
        :
        :"r" (task_to_schedule_p->esp),"r" (task_to_schedule_p->eip));
    }
}