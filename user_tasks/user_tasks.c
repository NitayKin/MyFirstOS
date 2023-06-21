#include "user_tasks.h"


mutex_ptr mutex_mem_first;
int32_t x = 0;

void first_task()
{
	mutex_mem_first = create_mutex_system_call();
	create_task_system_call(second_task,5);
	create_task_system_call(third_task,5);
	int tmp = 0;
	int tmp_2;
    while(tmp<5)
    {
    	while(lock_mutex_system_call(mutex_mem_first)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	tmp_2 = x;
    	wait_timer_ticks_system_call(30);
    	tmp_2++;
    	x=tmp_2;
    	unlock_mutex_system_call(mutex_mem_first); //unlocking the mutex
    	tmp++;
    }
    delete_task_system_call();
}

void second_task()
{
	int tmp = 0;
	int tmp_2;
    while(tmp<10000)
    {
    	while(lock_mutex_system_call(mutex_mem_first)!=SYS_CALL_SUCCESS); //trying to acquire lock, yielding cpu otherwise
    	tmp_2 = x;
    	tmp_2++;
    	x=tmp_2;
    	unlock_mutex_system_call(mutex_mem_first); //unlocking the mutex
    	tmp++;
    }
    delete_task_system_call();
}

void third_task()
{
    while(1)
    {
    	print_hex(&x,4);
    	wait_timer_ticks_system_call(10);
    }
}


void print_func_stub(char* string,uint32_t length)
{
	print_system_call(string, length);
}
