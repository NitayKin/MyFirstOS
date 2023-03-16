#include "user_tasks.h"
void empty_task()
{
    delete_task();
}

mutex_ptr mutex_mem;

void first_task()
{
	mutex_mem = create_mutex_system_call();
    while(1)
    {
    	while(lock_mutex_system_call(mutex_mem)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	print_system_call("abc", 3);
    	unlock_mutex_system_call(mutex_mem); //unlocking the mutex
    }
    delete_task();
}

void second_task()
{
    while(1)
    {
    	while(lock_mutex_system_call(mutex_mem)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	print_system_call("def", 3);
    	unlock_mutex_system_call(mutex_mem); //unlocking the mutex
    }
    delete_task();
}

void third_task()
{
    while(1)
    {
    	while(lock_mutex_system_call(mutex_mem)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	print_system_call("ghi", 3);
    	unlock_mutex_system_call(mutex_mem); //unlocking the mutex
    }
    delete_task();
}
