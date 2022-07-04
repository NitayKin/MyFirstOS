#include "user_tasks.h"
void first_task()
{
    while(1)
        print("a",1);
    delete_task();
}

void second_task()
{
    while(1)
        print("b",4);
    delete_task();
}