#include "idt.h"

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) //set specific inteerrupt in idt
{ 
    idt_entry_t* descriptor = &idt[vector];
 
    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08; // offset kernel code selector in GDT
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint32_t)isr >> 16;
    descriptor->reserved       = 0;
}

void empty_int_func(void* x)
{
    __asm__ volatile ("cli");
    //print("im inside an interrupt",23);
}

void empty_pit_func(void* x)
{
    __asm__ volatile ("cli");
    __asm__ volatile ("in al, 0x60"); //read information from the device
    __asm__ volatile ("mov al, 0x20");
    __asm__ volatile ("out 0x20, al"); //tell the PIC its over
}

void gpf_int_func(void* x)
{
    __asm__ volatile ("cli");
    print("GPF",3);
}


void idt_init() //init idt table
{
    __asm__ volatile ("cli");
    initialize_pic();
//    initialize_RTC();very unstable, leave for now.
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;


    for ( uint8_t i=0;i<IDT_MAX_DESCRIPTORS - 1;i++ )// set every interrupt to empty_func
    {
        idt_set_descriptor(i,(void*)empty_int_func,IDT_FLAG_HW); // intterupt number i will run function empty_func.
    }
    idt_set_descriptor(0x0d,(void*)gpf_int_func,IDT_FLAG_HW); // int 0x0d GPF
    idt_set_descriptor(0x20,(void*)timer_int_func,IDT_FLAG_HW); // int 0x20 PIT
    idt_set_descriptor(0x21,(void*)keyboard_int_func,IDT_FLAG_HW); // int 0x21 keyboard
//    idt_set_descriptor(0x70,(void*)timer_int_func,IDT_FLAG_HW); // int 0x70 RTC - very unstable, leave for now.
    idt_set_descriptor(0x80,(void*)system_call_handler,IDT_FLAG_USER); // int 0x80 system call handler
    

    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
}

void initialize_pic()
{
	out(0x20,0b00010001); // icw1 - general  send to PIC
    out(0xA0, 0b00010001); // icw 1 - send to secondary PIC

    out(0x21, 0x20); // icw2 - IVT number selector - send to PIC - IRQ 0..7<->software interrupt 0x20...0x27
    out(0xA1, 0x70); // icw2 - IVT number selector - send to secondary PIC - IRQ 8..15<->software interrupt 0x70...0x78

    out(0x21, 0x4); // icw3 - which pin to connect the secondary PIC - 0x04 => 0100, second bit (IR line 2)
    out(0xA1, 0x2);// icw3 - to secondary - 010=> IR line 2
    
    out(0x21, 1);// icw4 - 80x86 mode - primary PIC
    out(0xA1, 1);// icw4 - 80x86 mode - secondary PIC

    out(0x21, 0);// null data registers
    out(0xA1, 0);// null data registers
}

void initialize_RTC(void)
{
	char prev;
	out(0x70, 0x8B);// set index to register A, disable NMI
	__asm__ volatile ("in al, 0x71"); //read the current value of register B
    __asm__ volatile ("mov %0,al": "=r" (prev));
    prev = prev | 0x40;
	out(0x70, 0x8B);// set index again, (read reseting)
	out(0x71, prev);// write the previous value ORed with 0x40. This turns on bit 6 of register B
}
