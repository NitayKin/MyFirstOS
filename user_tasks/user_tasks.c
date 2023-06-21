#include "user_tasks.h"


mutex_ptr mutex_mem_first;
int32_t global_variable = 0;

void first_task()
{
	mutex_mem_first = create_mutex_system_call();
	create_task_system_call(second_task,5);
	create_task_system_call(third_task,5);
	int local_counter = 0;
	int local_tmp;
    while(local_counter<5)
    {
    	while(lock_mutex_system_call(mutex_mem_first)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	local_tmp = global_variable;
    	wait_timer_ticks_system_call(30);
    	local_tmp++;
    	global_variable=local_tmp;
    	unlock_mutex_system_call(mutex_mem_first); //unlocking the mutex
    	local_counter++;
    }
    delete_task_system_call();
}

void second_task()
{
	int local_counter = 0;
	int local_tmp;
    while(local_counter<10000)
    {
    	while(lock_mutex_system_call(mutex_mem_first)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	local_tmp = global_variable;
    	local_tmp++;
    	global_variable=local_tmp;
    	unlock_mutex_system_call(mutex_mem_first); //unlocking the mutex
    	local_counter++;
    }
    delete_task_system_call();
}

void third_task()
{
	int local_counter = 0;
    while(local_counter<7)
    {
    	print_hex(&global_variable,4);
    	wait_timer_ticks_system_call(50);
    	local_counter++;
    }
    delete_task_system_call();
}


void print_func_stub(char* string,uint32_t length)
{
	print_system_call(string, length);
}
