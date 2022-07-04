#include "auxility.h"

void print_esp()
{
    uint32_t my_esp;
    __asm__ volatile ("mov %0, esp":"=r" (my_esp));
    print_hex(&my_esp,4);
}