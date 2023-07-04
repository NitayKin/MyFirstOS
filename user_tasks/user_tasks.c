#include "user_tasks.h"


mutex_ptr mutex_mem_first;
int32_t global_variable = 0;

void increment_global_5_task()
{
	mutex_mem_first = create_mutex_system_call();
	create_task_system_call(increment_global_10000_task,7);
	create_task_system_call(print_global_task,10);
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

void increment_global_10000_task()
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

void print_global_task()
{
	int local_counter = 0;
    while(local_counter<7)
    {
    	print_func_stub("the counter is:",16);
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
