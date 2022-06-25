#include <stdint.h> //for type definitions
#include "print.h"
#ifndef paging_header
#define paging_header

extern uint32_t* page_directory __attribute__((aligned(4096)));
extern uint32_t* page_table __attribute__((aligned(4096)));
void paging_init();

#endif