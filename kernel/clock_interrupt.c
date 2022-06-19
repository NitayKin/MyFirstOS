#include "clock_interrupt.h"
#include "print.h"

void timer_int_func(void* x)
{
    __asm__ volatile ("in al, 0x60"); //read information from the device
    __asm__ volatile ("mov al, 0x20");
    __asm__ volatile ("out 0x20, al"); //tell the PIC its over
}