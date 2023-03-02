#include "user_tasks.h"
void empty_task()
{
    delete_task();
}

void first_task()
{
	mutex_ptr mutex_mem;
	mutex_mem = create_mutex_system_call();
	print_hex(&mutex_mem, 4);
	mutex_mem = create_mutex_system_call();
	print_hex(&mutex_mem, 4);
    while(1)
    {
    }
    delete_task();
}

void second_task()
{
    while(1)
    {
//        print_system_call("def",3);
    }
    delete_task();
}

void third_task()
{
    while(1)
    {
//        print_system_call("ghi",3);
    }
    delete_task();
}
