#include "user_tasks.h"
void empty_task() // creating it first, for some reason the first task always getting bugged.
{
    delete_task();
}

void first_task()
{
    while(1)
    {
        print("a",1);
    }
    delete_task();
}

void second_task()
{
    create_task(third_task);
    while(1)
    {
        print("b",1);
    }
    delete_task();
}

void third_task()
{
    uint16_t x =0;
    while(x!=0xff00)
    {
        print("c",1);
        x++;
    }
    delete_task();
}