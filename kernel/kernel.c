#include "print.h"
#include "idt.h"
#include "paging.h"
#include "tasks.h"
#include "../user_tasks/user_tasks.h"

__asm__("call main\n\t"  // jump to main always and hang
        "jmp $");


void main () 
{
        clear_screen();
        idt_init(); //idt initialization
        paging_init(); //paging initizalization
        create_task(first_task); //creating the first task
        #include "enter_user_mode.asm" //entering user mode ( loading TSS too )]]
        while(1){} //hang
}
