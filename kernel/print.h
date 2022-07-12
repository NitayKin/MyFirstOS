#ifndef print_header
#define print_header
#include <stdint.h> //for type definitions
#include "memory_locations_defintions.h"

#define MAX_VIDEO_MEM 4000

extern char* g_video_memory;


void clear_screen();// should be an interrupt!
void print(char*, int);// should be an interrupt!
void print_hex(char*, int);// should be an interrupt!

#endif