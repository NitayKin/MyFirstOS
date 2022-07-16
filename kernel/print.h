#ifndef print_header
#define print_header
#include <stdint.h> //for type definitions
#include "memory_locations_defintions.h"

#define MAX_VIDEO_MEM 4000

extern char* g_video_memory;


void clear_screen();// called by system call interrupt handler
void print(char*, int);// called by system call interrupt handler
void print_hex(char*, int);// called by system call interrupt handler

#endif