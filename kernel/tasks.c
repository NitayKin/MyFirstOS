#include "tasks.h"


TaskDescription tasks[256] = {[0 ... 255] = {0,0,0,0,0}};
uint8_t total_tasks = 0;
uint8_t currently_running_task_id = 0;

void create_task(void* task_address)
{
    for(int i=0;i<256;++i)
    {
        if(tasks[i].alive == false)
        {
            tasks[i].alive = true;
            tasks[i].ebp = (uint32_t)(USER_STACK_MEMORY_LOCATION + ((0x3000) *  i)); // every task gets 0x3000 stack space.
            tasks[i].esp = (uint32_t)(USER_STACK_MEMORY_LOCATION + ((0x3000) *  i)); // every task gets 0x3000 stack space.
            tasks[i].eip = (uint32_t*)task_address;
            tasks[i].id = total_tasks++;
            break;
        }
    }
}


void delete_task()
{
    uint32_t current_esp;
    __asm__ volatile("mov %0, esp\n\t" // move current esp location to local variable kb_char;
    : "=r" (current_esp)
    : );
    for(int i=0;i<256;++i) // search for the appropriate task based on the stack placement in memory
    {
        if( (tasks[i].esp>=current_esp) &&(current_esp>=tasks[i].esp - 0x3000) && (tasks[i].alive == true)) // esp in the task memory location - this is the apropriate task . zero it.
        {
            tasks[i].alive = false;
            tasks[i].ebp = 0;
            tasks[i].esp = 0;
            tasks[i].eip = 0;
            tasks[i].id = 0;
            total_tasks--;
            break;
        }
    }
}

void get_task_by_id(TaskDescription* td,uint8_t id)
{
    for(int i=0;i<256;++i)
    {
        if(tasks[i].id==id) // found the task
        {
            td->ebp = tasks[i].ebp;
            td->esp = tasks[i].esp;
            td->eip = tasks[i].eip;
            td->id = tasks[i].id;
            break;
        }
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