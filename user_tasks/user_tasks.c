#include "user_tasks.h"
void empty_task()
{
    delete_task();
}

mutex_ptr mutex_mem_first;
mutex_ptr mutex_mem_second;

void first_task()
{
	mutex_mem_first = create_mutex_system_call();
	mutex_mem_second = create_mutex_system_call();
	create_task_system_call(second_task,5);
	create_task_system_call(third_task,5);
    while(1)
    {
    	while(lock_mutex_system_call(mutex_mem_first)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	while(lock_mutex_system_call(mutex_mem_second)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	print_func_stub("abc", 3);
    	unlock_mutex_system_call(mutex_mem_first); //unlocking the mutex
    	unlock_mutex_system_call(mutex_mem_second); //unlocking the mutex
    }
    delete_task_system_call();
}

void second_task()
{
    while(1)
    {
    	while(lock_mutex_system_call(mutex_mem_first)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	while(lock_mutex_system_call(mutex_mem_second)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	print_func_stub("ghi", 3);
    	unlock_mutex_system_call(mutex_mem_first); //unlocking the mutex
    	unlock_mutex_system_call(mutex_mem_second); //unlocking the mutex
    	delete_mutex_system_call(mutex_mem_first);
    }
    delete_task_system_call();
}

void third_task()
{
    while(1)
    {
    	while(lock_mutex_system_call(mutex_mem_first)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	while(lock_mutex_system_call(mutex_mem_second)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	wait_timer_ticks_system_call(20); // waiting
    	print_func_stub("def", 3);
    	unlock_mutex_system_call(mutex_mem_first); //unlocking the mutex
    	unlock_mutex_system_call(mutex_mem_second); //unlocking the mutex
        delete_task_system_call(); //deleting task
    }
}


void print_func_stub(char* string,uint32_t length)
{
	print_system_call(string, length);
}
