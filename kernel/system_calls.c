#include "system_calls.h"

void print_system_call(char* string, uint32_t bytes)
{
    if(bytes>0)
    {
        __asm__ volatile("pushf");
        for(uint32_t current_byte = 0;current_byte<bytes;++current_byte)
        {
            __asm__ volatile("push ebx"); // save ebx value
            __asm__ volatile("push eax"); // save eax value

            __asm__ volatile("mov ebx,%0"::"r" (string + current_byte)); // put the next char location inside ebx]
            __asm__ volatile("mov eax,1"); // eax= 1 means print interrupt
            __asm__ volatile("int 0x80"); // call system call interrupt

            __asm__ volatile("pop eax"); // return eax value
            __asm__ volatile("pop ebx"); // return ebx value
        }
        __asm__ volatile("popf");
    }
}