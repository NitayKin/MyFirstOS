#include "user_tasks.h"
void empty_task()
{
    delete_task();
}

mutex_ptr mutex_mem;

void first_task()
{
	mutex_mem = create_mutex_system_call();
	lock_mutex_system_call(mutex_mem);
    while(1)
    {
    	print_system_call("abc", 3);
    }
    delete_task();
}

void second_task()
{
	lock_mutex_system_call(mutex_mem);
    while(1)
    {
        print_system_call("def",3);
    }
    delete_task();
}

void third_task()
{
	lock_mutex_system_call(mutex_mem);
    while(1)
    {
        print_system_call("ghi",3);
    }
    delete_task();
}
