#include "system_call_interrupt.h"

void system_call_handler(void* x)
{
    uint32_t system_call_number;
    char* char_pointer; // for printing function
    __asm__ volatile ("cli");
    __asm__ volatile ("mov %0,[ebp-0x0c]": "=r" (system_call_number)); // get the last eax from the stack (0x0c) - which insicates which system call it is
    switch(system_call_number)
    {
        case 1: // print interrupt
            __asm__ volatile ("mov %0,ebx": "=r" (char_pointer)); // get pointer of char to print
            print(char_pointer,1);
            break;


        default:
            break;
    }
    __asm__ volatile ("sti");
}