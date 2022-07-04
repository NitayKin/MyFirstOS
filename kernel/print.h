#ifndef print_header
#define print_header
#include <stdint.h> //for type definitions

#define MAX_VIDEO_MEM 4000

extern char* g_video_memory;

void clear_screen();
void print(char*, int);
void print_hex(char*, int);

#endif