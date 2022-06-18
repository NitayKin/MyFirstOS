#include <stdint.h> //for type definitions

#define IDT_MAX_DESCRIPTORS 256

void empty_int_func(void*) __attribute__((interrupt)); //declare interrupt functions
void timer_int_func(void*) __attribute__((interrupt));
void keyboard_int_func(void*) __attribute__((interrupt));


typedef struct {
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     reserved;     // Set to zero
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

typedef struct { //IDTR structure
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed)) idtr_t;

__attribute__((aligned(0x10)))static idt_entry_t idt[256]; // Create an array of IDT entries; aligned for performance
static idtr_t idtr;

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

void timer_int_func(void* x)
{
    print("inside timer int",16);
    __asm__ volatile ("in al, 0x60"); //read information from the device
    __asm__ volatile ("mov al, 0x20");
    __asm__ volatile ("out 0x20, al"); //tell the PIC its over
}

void keyboard_int_func(void* x)
{
    print("inside keyboard int",16);
    __asm__ volatile ("in al, 0x60"); //read information from the device
    __asm__ volatile ("mov al, 0x20");
    __asm__ volatile ("out 0x20, al");//tell the PIC its over
}

void idt_init() { //init idt table
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;


    for ( uint8_t i=0;i<IDT_MAX_DESCRIPTORS - 1;++i) // set every interrupt to empty_func ( int 0x08 clock making restarts if not)
    {
        idt_set_descriptor(i,(void*)empty_int_func,0x8E); // intterupt number i will run function empty_func.
    }
    idt_set_descriptor(0x8,(void*)timer_int_func,0x8E); // int 0x08 timer
    idt_set_descriptor(0x9,(void*)keyboard_int_func,0x8E); // int 0x09 keyboard


    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
}
