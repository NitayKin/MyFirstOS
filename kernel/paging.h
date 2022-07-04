#ifndef paging_header
#define paging_header
#include <stdint.h> //for type definitions
#include "print.h"
#include "memory_locations_defintions.h"

extern uint32_t* page_directory __attribute__((aligned(4096)));
extern uint32_t* page_table __attribute__((aligned(4096)));
void paging_init();

#endif