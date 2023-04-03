#include "tasks.h"


task_description_t tasks[MAX_TASKS] = {[0 ... MAX_TASKS-1] = {0,0,0,0,{0,0,0},0,0,0,0,0,0,0,0,0}};
uint8_t total_tasks = 1; // always at least 1 - the kernel\task which spawned from him.
uint8_t currently_running_task_id = 0; // 0 at start is the kernel task. it will be deleted after initializing everything, and could be used by others.

status create_task(void* task_address)
{
	int8_t next_free_task_id = find_empty_task_slot();
	if(next_free_task_id!=INTERNAL_ERROR){
		tasks[next_free_task_id].status = alive;
		tasks[next_free_task_id].ebp = (uint32_t)(USER_STACK_MEMORY_LOCATION + (uint32_t)((0x3000) *  next_free_task_id)); // every task gets 0x3000 stack space.
		tasks[next_free_task_id].esp = (uint32_t)(USER_STACK_MEMORY_LOCATION + (uint32_t)((0x3000) *  next_free_task_id)); // every task gets 0x3000 stack space.
		tasks[next_free_task_id].eip = (uint32_t)task_address;
		tasks[next_free_task_id].eflags = (uint32_t)0x202;
		tasks[next_free_task_id].id = next_free_task_id;
		total_tasks++;
		return SYS_CALL_SUCCESS;
	}
	else
		return SYS_CALL_ERR;
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
    tasks[currently_running_task_id].total_mutex_own = 0;
    memset(tasks[currently_running_task_id].mutex_own, 0, sizeof(mutex_ptr)*3);
    tasks[currently_running_task_id].mutex_wait = 0;
    total_tasks--;
}

int8_t find_empty_task_slot()
{
	for(uint8_t tmp_task_id=0;tmp_task_id<MAX_TASKS;++tmp_task_id){
		if(tasks[tmp_task_id].status == dead){
			return tmp_task_id;
		}
	}
	return INTERNAL_ERROR;
}


void get_task_by_id(task_description_t* td,uint8_t id)
{
    if(tasks[id].status==alive){ // the task is alive
        td->ebp = tasks[id].ebp;
        td->esp = tasks[id].esp;
        td->eip = tasks[id].eip;
        td->id = tasks[id].id;
    }
}

void print_tasks()
{
    for(int i=0;i<MAX_TASKS;++i){
        if(tasks[i].status==alive){
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
    task_description_t temp_task = {1,1,1,1};
    task_description_t* temp_task_p= &temp_task;
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
