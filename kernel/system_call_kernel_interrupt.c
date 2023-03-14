#include "system_call_kernel_interrupt.h"

/* this is system_call_handel(int 0x80), edx register indicates which function the user wanted to do.
 * ebx and ecx are general registers that stored the data for the function requested.
 * if the requested function needs to return a variable, it will return it in ebx
 */
void system_call_handler(void* x)
{
    __asm__ volatile ("cli");
    uint32_t system_call_number; // with save edx - the
    uint32_t ebx_data; // will save ebx - data to requested function.
    uint32_t ecx_data; // will save ecx - data to requested function.
    __asm__ volatile ("mov %0,edx": "=r" (system_call_number)); // get the last edx, which indicates which system call it is

    switch(system_call_number)
    {
        case 1: // print interrupt - ecx is string length, ebx is the pointer to the character.
            __asm__ volatile ("mov %0,ebx": "=r" (ebx_data)); // get pointer of char to print
        	__asm__ volatile ("mov %0,ecx": "=r" (ecx_data)); // get the last ecx - which indicates string length
            print((char*)ebx_data,ecx_data);
            break;

        case 2: // create_mutex - returning a pointer to a mutex the user can use to lock and unlock.
    		__asm__ volatile("mov ebx,%0"::"r" (create_mutex())); // put the mutex location inside ebx
        	break;

        case 3: // delete_mutex - deleting a mutex
            __asm__ volatile ("mov %0,ebx": "=r" (ebx_data)); // get mutex_ptr to the mutex we want to delete
    		__asm__ volatile("mov ebx,%0"::"r" (delete_mutex(ebx_data))); // delete the mutex, and return the status
        	break;

        case 4: // lock_mutex - locking a mutex or waiting untill it is unlocked
        	status lock_mutex_status;
            __asm__ volatile ("mov %0,ebx": "=r" (ebx_data)); // get mutex_ptr to the mutex we want to lock
            lock_mutex_status = lock_mutex(ebx_data); //get the lock mutex status
            if(lock_mutex_status == SYS_CALL_ERR){ //if there is an error in the mutex aqcuire
            	context_switch(); //switch to the next task
            	timer_ticks = 0; //reset the timer
            }
    		__asm__ volatile("mov ebx,%0"::"r" (lock_mutex_status)); // lock the mutex, and return the status
        	break;

        case 5: // unlock_mutex - unlocking a mutex
            __asm__ volatile ("mov %0,ebx": "=r" (ebx_data)); // get mutex_ptr to the mutex we want to unlock
    		__asm__ volatile("mov ebx,%0"::"r" (unlock_mutex(ebx_data))); // unlock the mutex, and return the status
        	break;

        default:
            break;
    }

}
