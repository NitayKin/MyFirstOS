#include "clock_interrupt.h"

uint8_t timer_ticks = 0;


void timer_int_func(void* x)
{
    __asm__ volatile ("cli");
    __asm__ volatile ("in al, 0x60"); //read information from the device
    __asm__ volatile ("mov al, 0x20");
    __asm__ volatile ("out 0x20, al"); //tell the PIC its over
    timer_ticks++; //increasing timer counter

    if(timer_ticks >= 20){
    	context_switch(); // calling the context switch
    	timer_ticks = 0; // reset timer watcher
    }
}
