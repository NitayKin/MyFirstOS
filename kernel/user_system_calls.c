#include "user_system_calls.h"

// print system call request
void print_system_call(char* string, uint32_t bytes)
{
    if(bytes>0)
    {
		PUSH_GENERAL_REG_NO_EAX();

		__asm__ volatile("mov edx,1"); // edx= 1 means print interrupt
		__asm__ volatile("mov ebx,%0"::"r" (string)); // put the next char location inside ebx
		__asm__ volatile("mov ecx,%0"::"r" (bytes)); // put the string length inside ecx
		__asm__ volatile("int 0x80"); // call system call interrupt

		POP_GENERAL_REG_NO_EAX();
    }
}

// create mutex system call request
void* create_mutex_system_call(void)
{
	void* memory_location;

	PUSH_GENERAL_REG_NO_EAX();

	__asm__ volatile("mov edx,2"); // edx= 2 means get mutex system call
	__asm__ volatile("int 0x80"); // call system call interrupt
	__asm__ volatile ("mov %0,ebx": "=r" (memory_location)); // get the memory location from the interrupt

	POP_GENERAL_REG_NO_EAX();
	return memory_location;
}

// delete mutex system call request
int8_t delete_mutex_system_call(mutex_ptr mutex_memory_location)
{
	status status;

	PUSH_GENERAL_REG_NO_EAX();

	__asm__ volatile("mov edx,3"); // edx= 3 means delete mutex system call
	__asm__ volatile("mov ebx,%0"::"r" (mutex_memory_location)); // put the mutex_ptr inside ebx
	__asm__ volatile("int 0x80"); // call system call interrupt
	__asm__ volatile ("mov %0,ebx": "=r" (status)); // get status from the system call

	POP_GENERAL_REG_NO_EAX();
	return status;
}

status lock_mutex_system_call(mutex_ptr mutex_memory_location)
{
	status status;

	PUSH_GENERAL_REG_NO_EAX();

	__asm__ volatile("mov edx,4"); // edx= 4 means lock mutex system call
	__asm__ volatile("mov ebx,%0"::"r" (mutex_memory_location)); // put the mutex_ptr inside ebx
	__asm__ volatile("int 0x80"); // call system call interrupt
	__asm__ volatile ("mov %0,ebx": "=r" (status)); // get status from the system call

	POP_GENERAL_REG_NO_EAX();
	return status;
}

status unlock_mutex_system_call(mutex_ptr mutex_memory_location)
{
	status status;

	PUSH_GENERAL_REG_NO_EAX();

	__asm__ volatile("mov edx,5"); // edx= 5 means unlock mutex system call
	__asm__ volatile("mov ebx,%0"::"r" (mutex_memory_location)); // put the mutex_ptr inside ebx
	__asm__ volatile("int 0x80"); // call system call interrupt
	__asm__ volatile ("mov %0,ebx": "=r" (status)); // get status from the system call

	POP_GENERAL_REG_NO_EAX();
	return status;
}

void wait_timer_ticks_system_call(uint32_t ticks_to_wait)
{
    if(ticks_to_wait>0)
    {
		PUSH_GENERAL_REG_NO_EAX();

		__asm__ volatile("mov edx,6"); // edx= 6 means wait interrupt
		__asm__ volatile("mov ebx,%0"::"r" (ticks_to_wait)); // put the ticks to wait inside ebx
		__asm__ volatile("int 0x80"); // call system call interrupt

		POP_GENERAL_REG_NO_EAX();
    }
}

status create_task_system_call(uint32_t mem_location)
{
	status status;

	PUSH_GENERAL_REG_NO_EAX();

	__asm__ volatile("mov edx,7"); // edx= 7 means create task
	__asm__ volatile("mov ebx,%0"::"r" (mem_location)); // put the memory location of the new task inside ebx
	__asm__ volatile("int 0x80"); // call system call interrupt
	__asm__ volatile ("mov %0,ebx": "=r" (status)); // get status from the system call

	POP_GENERAL_REG_NO_EAX();
	return status;
}

void delete_task_system_call()
{
	PUSH_GENERAL_REG_NO_EAX();

	__asm__ volatile("mov edx,8"); // edx= 8 means delete task
	__asm__ volatile("int 0x80"); // call system call interrupt

	POP_GENERAL_REG_NO_EAX();
}
