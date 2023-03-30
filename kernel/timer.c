#include "timer.h"

uint16_t timer_ticks = 0;


void timer_int_func(void* x)
{
	char tmp;
    __asm__ volatile ("cli");
    in(0x60,tmp);//read information from the device
    out(PIC1_COMMAND, 0x20);//tell the PIC its over

    /*RTC - not stable, leave for now...
    out(0x70, 0x0C);//select register C - (if register C is not read after an IRQ 8, then the interrupt will not happen again.)
    in(0x71,tmp); //throw away contents
    */

    decrease_global_waiting_timer_ticks(); //decreasing tasks ticks to wait globally

    timer_ticks++; //increasing timer counter

    if(timer_ticks >= TIMER_TICKS_PER_SECOND){
    	context_switch(); // calling the context switch
    	timer_ticks = 0; // reset timer watcher
    }
    /*RTC - not stable, leave for now...
    out(PIC2_COMMAND, 0x20);//tell the PIC and secondary pic its over
    out(PIC1_COMMAND, 0x20);
    */
}

void wait_timer_ticks(uint32_t ticks_to_wait)
{
	tasks[currently_running_task_id].ticks_to_wait = ticks_to_wait;
	tasks[currently_running_task_id].status = waiting;
}

void decrease_global_waiting_timer_ticks(void)
{
	 for(int i=0;i<MAX_TASKS;++i){
	        if(tasks[i].ticks_to_wait>0){
	        	tasks[i].ticks_to_wait--;
	        	if(tasks[i].ticks_to_wait == 0)
	        		tasks[i].status = alive;
	        }
	    }
}
