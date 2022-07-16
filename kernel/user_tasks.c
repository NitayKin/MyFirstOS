#include "user_tasks.h"
void empty_task() // creating it first, for some reason the first task always getting bugged.
{
    delete_task();
}

void first_task()
{
    while(1)
    {
        print_system_call("b",1);
    }
    delete_task();
}

void second_task()
{
    while(1)
    {
        print_system_call("d",1);
    }
    delete_task();
}

void third_task()
{
    while(1)
    {
        print_system_call("f",1);
    }
    delete_task();
}