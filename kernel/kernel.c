__asm__("call main\n\t"  // jump to main always and hang
        "jmp $");


void main () {
// Create a pointer to a char , and point it to the first text cell of
// video memory (i.e. the top - left of the screen )
idt_init();
char * video_memory = ( char *) 0xb8000 ;
// At the address pointed to by video_memory , store the character ’X’
// (i.e. display ’X’ in the top - left of the screen ).
* video_memory++ = 'x';
* video_memory++ = 0x0f;
* video_memory++ = 'z';
* video_memory++ = 0x0f;
}