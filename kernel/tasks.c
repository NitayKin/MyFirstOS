#include "tasks.h"


TaskDescription tasks[256] = {[0 ... 255] = {0,0,0,0,0,0,0,0}};
uint8_t total_tasks = 1; // always at least 1 - the kernel.
uint8_t currently_running_task_id = KERNEL_TASK_CODE; // 0 is the kernel task.

void create_task(void* task_address)
{
	tasks[total_tasks].status = alive;
	tasks[total_tasks].ebp = (uint32_t)(USER_STACK_MEMORY_LOCATION + (uint32_t)((0x3000) *  total_tasks)); // every task gets 0x3000 stack space.
	tasks[total_tasks].esp = (uint32_t)(USER_STACK_MEMORY_LOCATION + (uint32_t)((0x3000) *  total_tasks)); // every task gets 0x3000 stack space.
	tasks[total_tasks].eip = (uint32_t)task_address;
	tasks[total_tasks].eax = (uint32_t)0x0;
	tasks[total_tasks].ecx = (uint32_t)0x0;
	tasks[total_tasks].ebx = (uint32_t)0x0;
	tasks[total_tasks].edx = (uint32_t)0x0;
	tasks[total_tasks].eflags = (uint32_t)0x202;
	tasks[total_tasks].id = total_tasks;
	total_tasks++;
}


void delete_task()
{
    tasks[currently_running_task_id].status = dead;
    tasks[currently_running_task_id].ebp = 0;
    tasks[currently_running_task_id].esp = 0;
    tasks[currently_running_task_id].eip = 0;
    tasks[currently_running_task_id].eax = (uint32_t)0x0;
    tasks[currently_running_task_id].ecx = (uint32_t)0x0;
    tasks[currently_running_task_id].edx = (uint32_t)0x0;
    tasks[currently_running_task_id].eflags = (uint32_t)0x0;
    tasks[currently_running_task_id].id = 0;
    total_tasks--;
    ticks = 20; // so the sceduler will schedule right away at next timer interrupt.
}

void get_task_by_id(TaskDescription* td,uint8_t id)
{
    if(tasks[id].status==alive) // the task is alive
    {
        td->ebp = tasks[id].ebp;
        td->esp = tasks[id].esp;
        td->eip = tasks[id].eip;
        td->id = tasks[id].id;
    }
}

void print_tasks()
{
    for(int i=0;i<256;++i)
    {
        if(tasks[i].status==alive)
        {
            print("new task:",9);
            print("ebp of task:",12);
            print_hex(&tasks[i].ebp,4);
            print("eip of task:",12);
            print_hex(&tasks[i].eip,4);
            print("id of task:",12);
            print_hex(&tasks[i].id,1);
            print("esp of task:",12);
            print_hex(&tasks[i].esp,4);
            print("     ",5);
        }
    }
}

void print_task_id(uint8_t id)
{
    TaskDescription temp_task = {1,1,1,1};
    TaskDescription* temp_task_p= &temp_task;
    get_task_by_id(temp_task_p,id);
    print("the task:",9);
    print("ebp of task:",12);
    print_hex(&temp_task_p->ebp,4);
    print("eip of task:",12);
    print_hex(&temp_task_p->eip,4);
    print("id of task:",12);
    print_hex(&temp_task_p->id,1);
    print("esp of task:",12);
    print_hex(&temp_task_p->esp,4);
    print("     ",5);
}
