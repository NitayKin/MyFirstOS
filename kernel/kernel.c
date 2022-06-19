#include "print.h"
#include "idt.h"

__asm__("call main\n\t"  // jump to main always and hang
        "jmp $");


void main () 
{
        idt_init();
}