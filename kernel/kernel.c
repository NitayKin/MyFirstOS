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
        tasks[currently_running_task_id].status = alive; // making this task alive, so create_task will not override it
        #include "enter_user_mode.asm" //entering user mode ( loading TSS too )]]
        create_task_system_call(first_task); //creating the first task
        delete_task_system_call(); //deleting this task
}
