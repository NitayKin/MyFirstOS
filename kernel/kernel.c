#include "print.h"
#include "idt.h"
#include "paging.h"

__asm__("call main\n\t"  // jump to main always and hang
        "jmp $");


void main () 
{
        idt_init(); //idt initialization
        paging_init(); //paging initizalization
        #include "enter_user_mode.inc" //entering user mode ( loading TSS too )
        clear_screen();
}