#ifndef system_call_header
#define system_call_header

#include <stdint.h> //for type definitions
#include "auxility.h"
#include "common_defintions.h"

void print_system_call(char*,uint32_t) ;
void* create_mutex_system_call(void);
int8_t delete_mutex_system_call(mutex_ptr);
status lock_mutex_system_call(mutex_ptr);
status unlock_mutex_system_call(mutex_ptr);

#endif
