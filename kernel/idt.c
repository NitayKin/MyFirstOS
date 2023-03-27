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
    __asm__ volatile("push eax");

    __asm__ volatile("mov al, 0b00010001"); // icw1 - general
    __asm__ volatile("out 0x20, al"); // send to PIC
    __asm__ volatile("out 0xA0, al"); // send to secondary PIC

    __asm__ volatile("mov al, 0x20"); // icw2 - IVT number selector
    __asm__ volatile("out 0x21, al"); // send to PIC - IRQ 0..7<->software interrupt 0x20...0x27
    __asm__ volatile("mov al, 0x70"); // icw2 - IVT number selector
    __asm__ volatile("out 0xA1, al"); // send to secondary PIC - IRQ 8..15<->software interrupt 0x70...0x78

    __asm__ volatile("mov al, 0x4"); // icw3 - which pin to connect the secondary PIC
    __asm__ volatile("out 0x21, al"); // 0x04 => 0100, second bit (IR line 2)
    __asm__ volatile("mov al, 0x2"); // icw3 - to secondary
    __asm__ volatile("out 0xA1, al");//010=> IR line 2
    
    __asm__ volatile("mov al, 1"); // icw4 - 80x86 mode
    __asm__ volatile("out 0x21, al"); // primary PIC
    __asm__ volatile("out 0xA1, al"); // secondary PIC

    __asm__ volatile("mov al, 0"); // null data registers
    __asm__ volatile("out 0x21, al"); 
    __asm__ volatile("out 0xA1, al"); 



    __asm__ volatile("pop eax");
}

void initialize_RTC(void)
{
	char prev;
    __asm__ volatile("mov al, 0x8B");
	__asm__ volatile("out 0x70, al");// set index to register A, disable NMI
	__asm__ volatile ("in al, 0x71"); //read the current value of register B
    __asm__ volatile ("mov %0,al": "=r" (prev));
    prev = prev | 0x40;
    __asm__ volatile("mov al, 0x8B");
	__asm__ volatile("out 0x70, al");// set index again, (read reseting)
	__asm__ volatile ("mov al, %0"::"r" (prev));
	__asm__ volatile("out 0x71, al");// write the previous value ORed with 0x40. This turns on bit 6 of register B
}
