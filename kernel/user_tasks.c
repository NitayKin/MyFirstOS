#include "user_tasks.h"
void first_task()
{
    while(1){
        if(check++ == 0xfff)
        {
            print("a",1);
            check = 0;
        }
        }
    delete_task();
}

void second_task()
{
    while(1){
        if(check++ == 0xfff)
        {
            print("b",1);
            check = 0;
        }
        }
    delete_task();
}