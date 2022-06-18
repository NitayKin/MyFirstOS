__asm__("call main\n\t"  // jump to main always and hang
        "jmp $");


void main () 
{
        idt_init();
        print("inside 1",8);
        __asm__ volatile("hlt");
        print("inside 2",8);
        __asm__ volatile("hlt");
        print("inside 3",8);
}