#ifndef memory_manager_header
#define memory_manager_header

#include <stdint.h> //for type definitions
#include "print.h"
#include "memory_locations_defintions.h"

uint32_t total_bytes_allocated; // every request gets 
void* malloc(uint32_t);
#endif