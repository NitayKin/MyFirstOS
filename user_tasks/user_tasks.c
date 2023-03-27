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
    while(1)
    {
    	while(lock_mutex_system_call(mutex_mem_first)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	while(lock_mutex_system_call(mutex_mem_second)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	print_func_stub("abc", 3);
    	wait_timer_ticks_system_call(20);
    	unlock_mutex_system_call(mutex_mem_first); //unlocking the mutex
    	unlock_mutex_system_call(mutex_mem_second); //unlocking the mutex
    	wait_timer_ticks_system_call(5);
    }
    delete_task();
}

void second_task()
{
    while(1)
    {
    	while(lock_mutex_system_call(mutex_mem_first)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	while(lock_mutex_system_call(mutex_mem_second)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	print_func_stub("def", 3);
    	unlock_mutex_system_call(mutex_mem_first); //unlocking the mutex
    	unlock_mutex_system_call(mutex_mem_second); //unlocking the mutex
    	delete_mutex_system_call(mutex_mem_first);
    }
    delete_task();
}

void third_task()
{
    while(1)
    {
    	while(lock_mutex_system_call(mutex_mem_first)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	while(lock_mutex_system_call(mutex_mem_second)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	print_func_stub("ghi", 3);
    	unlock_mutex_system_call(mutex_mem_first); //unlocking the mutex
    	unlock_mutex_system_call(mutex_mem_second); //unlocking the mutex
    	delete_mutex_system_call(mutex_mem_second);
    }
    delete_task();
}


void print_func_stub(char* string,uint32_t length)
{
	print_system_call(string, length);
}
