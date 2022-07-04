#include "clock_interrupt.h"

uint8_t ticks = 0;


void timer_int_func(void* x)
{
    __asm__ volatile ("in al, 0x60"); //read information from the device
    __asm__ volatile ("mov al, 0x20");
    __asm__ volatile ("out 0x20, al"); //tell the PIC its over
    if(ticks++ == 20)
    {
        ticks = 0;
        scheduler();
    }
}