#include "tasks.h"


TaskDescription tasks[256] = {[0 ... 255] = {0,0,0,0,0,0,0,0}};
uint8_t total_tasks = 0;
uint8_t currently_running_task_id = 230;

uint32_t check = 0;

void create_dummy_task(void* task_address)
{
        tasks[0].alive = true;
        tasks[0].ebp = (uint32_t)(USER_STACK_MEMORY_LOCATION + (uint32_t)((0x3000))); // every task gets 0x3000 stack space.
        tasks[0].esp = (uint32_t)(USER_STACK_MEMORY_LOCATION + (uint32_t)((0x3000))); // every task gets 0x3000 stack space.
        tasks[0].eip = (uint32_t)task_address;
        tasks[0].eax = (uint32_t)0x0;
        tasks[0].ecx = (uint32_t)0x0;
        tasks[0].edx = (uint32_t)0x0;
        tasks[0].eflags = (uint32_t)0x202;
        tasks[0].id = 0;
        total_tasks++;
}

void create_task(void* task_address)
{
    for(int i=1;i<256;++i)
    {
        if(tasks[i].alive == false)
        {
            tasks[i].alive = true;
            tasks[i].ebp = (uint32_t)(USER_STACK_MEMORY_LOCATION + (uint32_t)((0x3000) *  i)); // every task gets 0x3000 stack space.
            tasks[i].esp = (uint32_t)(USER_STACK_MEMORY_LOCATION + (uint32_t)((0x3000) *  i)); // every task gets 0x3000 stack space.
            tasks[i].eip = (uint32_t)task_address;
            tasks[i].eax = (uint32_t)0x0;
            tasks[i].ecx = (uint32_t)0x0;
            tasks[i].edx = (uint32_t)0x0;
            tasks[i].eflags = (uint32_t)0x202;
            tasks[i].id = i;
            total_tasks++;
            break;
        }
    }
}


void delete_task()
{
    tasks[currently_running_task_id].alive = false;
    tasks[currently_running_task_id].ebp = 0;
    tasks[currently_running_task_id].esp = 0;
    tasks[currently_running_task_id].eip = 0;
    tasks[currently_running_task_id].eax = (uint32_t)0x0;
    tasks[currently_running_task_id].ecx = (uint32_t)0x0;
    tasks[currently_running_task_id].edx = (uint32_t)0x0;
    tasks[currently_running_task_id].eflags = (uint32_t)0x0;
    tasks[currently_running_task_id].id = 0;
    total_tasks--;
    ticks = 20;
}

void get_task_by_id(TaskDescription* td,uint8_t id)
{
    if(tasks[id].alive==true) // the task is alive
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
        if(tasks[i].alive==true)
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