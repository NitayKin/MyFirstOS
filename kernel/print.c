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
    g_video_memory = ( char *) 0xb8000;
}
void print(char* word, int length) //printing string on screen
{
    for(int i=0;i<length;++i)
    {
        if ( ((uint32_t)g_video_memory - (uint32_t)MAX_VIDEO_MEM) == (uint32_t)0xb8000) //return back up
            g_video_memory = ( char *) 0xb8000;
        * g_video_memory++ = *((char*)word);
        * g_video_memory++ = 0x0f;
        word++;
    }
}
void print_hex(char* word, int length) //printing string on screen
{
    for(int i=0;i<length;++i)
    {
        char second_hex = (uint8_t)((uint8_t)(*(word)>>4)&0x0f);
        char first_hex = (uint8_t)((uint8_t)(*(word))&0x0f);
        switch ((uint8_t)second_hex)
        {
        case 0:
            print("0",1);
            break;
        case 1:
            print("1",1);
            break;
        
        case 2:
            print("2",1);
            break;
        
        case 3:
            print("3",1);
            break;
        
        case 4:
            print("4",1);
            break;
        
        case 5:
            print("5",1);
            break;
        
        case 6:
            print("6",1);
            break;
        
        case 7:
            print("7",1);
            break;
        
        case 8:
            print("8",1);
            break;
        
        case 9:
            print("9",1);
            break;
        
        case 10:
            print("A",1);
            break;
        
        case 11:
            print("B",1);
            break;
        
        case 12:
            print("C",1);
            break;
        
        case 13:
            print("D",1);
            break;
        
        case 14:
            print("E",1);
            break;
                
        case 15:
            print("F",1);
            break;
        
        default:
            break;
        }

        switch ((uint8_t)first_hex)
        {
        case 0:
            print("0",1);
            break;
        case 1:
            print("1",1);
            break;
        
        case 2:
            print("2",1);
            break;
        
        case 3:
            print("3",1);
            break;
        
        case 4:
            print("4",1);
            break;
        
        case 5:
            print("5",1);
            break;
        
        case 6:
            print("6",1);
            break;
        
        case 7:
            print("7",1);
            break;
        
        case 8:
            print("8",1);
            break;
        
        case 9:
            print("9",1);
            break;
        
        case 10:
            print("A",1);
            break;
        
        case 11:
            print("B",1);
            break;
        
        case 12:
            print("C",1);
            break;
        
        case 13:
            print("D",1);
            break;
        
        case 14:
            print("E",1);
            break;
                
        case 15:
            print("F",1);
            break;
        
        default:
            break;
        }
        word++;
    }
}