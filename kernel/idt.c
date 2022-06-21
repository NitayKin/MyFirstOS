#include "clock_interrupt.h"
#include "keyboard_interrupt.h"
#include "idt.h"

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) { //set specific inteerrupt in idt
    idt_entry_t* descriptor = &idt[vector];
 
    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint32_t)isr >> 16;
    descriptor->reserved       = 0;
}

void empty_int_func(void* x)
{
}


void idt_init() { //init idt table
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;


    for ( uint8_t i=0;i<IDT_MAX_DESCRIPTORS - 1;++i) // set every interrupt to empty_func ( int 0x08 clock making restarts if not)
    {
        idt_set_descriptor(i,(void*)empty_int_func,0xEE); // intterupt number i will run function empty_func.
    }
    idt_set_descriptor(0x8,(void*)timer_int_func,0xEE); // int 0x08 timer
    idt_set_descriptor(0x9,(void*)keyboard_int_func,0xEE); // int 0x09 keyboard


    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
}
