#include "user_tasks.h"
void empty_task()
{
    delete_task();
}

void first_task()
{
    while(1)
    {
        print_system_call("abc",3);
    }
    delete_task();
}

void second_task()
{
    while(1)
    {
        print_system_call("def",3);
    }
    delete_task();
}

void third_task()
{
    while(1)
    {
        print_system_call("ghi",3);
    }
    delete_task();
}
