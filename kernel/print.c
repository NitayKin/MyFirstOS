#include <stdint.h> //for type definitions
#include "print.h"

char* g_video_memory = ( char *) 0xb8000; //mmio of screen
void clear_screen()
{
    for(unsigned int i = 0xb8000;i<(0xb8000 + 4000);)
    {
        *((char*)i++) = 0x00;
        *((char*)i++) = 0x00;
    }
}
void print(char* word, int length) //printing string on screen
{
    for(int i=0;i<length;++i)
    {
        if ( ((uint32_t)g_video_memory - (uint32_t)MAX_VIDEO_MEM) == (uint32_t)0xb8000)
            g_video_memory = ( char *) 0xb8000;
        * g_video_memory++ = *word;
        * g_video_memory++ = 0x0f;
        word++;
    }
}