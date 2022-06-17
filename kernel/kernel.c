__asm__("call main\n\t"  // jump to main always and hang
        "jmp $");


void main () 
{
        idt_init();
        for (int i=0;i<200;++i)
        {
                print("i am alive!",11);
        }
}