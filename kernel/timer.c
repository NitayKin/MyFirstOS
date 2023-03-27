#include "timer.h"

uint16_t timer_ticks = 0;


void timer_int_func(void* x)
{
    __asm__ volatile ("cli");
    __asm__ volatile ("in al, 0x60"); //read information from the device
    __asm__ volatile ("mov al, 0x20");
    __asm__ volatile ("out 0x20, al"); //tell the PIC its over
    /*RTC - not stable, leave for now...
    __asm__ volatile ("mov al, 0x0C");
    __asm__ volatile ("out 0x70, al"); //select register C - (if register C is not read after an IRQ 8, then the interrupt will not happen again.)
    __asm__ volatile ("in al, 0x71"); //throw away contents
    */

    decrease_global_waiting_timer_ticks(); //decreasing tasks ticks to wait globally

    timer_ticks++; //increasing timer counter

    if(timer_ticks >= TIMER_TICKS_PER_SECOND){
    	context_switch(); // calling the context switch
    	timer_ticks = 0; // reset timer watcher
    }
    /*RTC - not stable, leave for now...
    __asm__ volatile ("mov al, 0x20");
    __asm__ volatile ("out 0xA0, al");
    __asm__ volatile ("out 0x20, al");//tell the secondary PIC its over
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
