#ifndef memory_location_definitions_header
#define memory_location_definitions_header

#define PAGE_DIRECTORY_MEMORY_LOCATION 0x900000
#define PAGE_TABLES_MEMORY_LOCATION 0xa00000
#define KERNEL_STACK_MEMORY_LOCATION 0x50000000 //interrupts - defined in the tss
#define USER_STACK_MEMORY_LOCATION 0x20000000
#define KERNEL_FUNCTION_MEMORY_LOCATION 0xd000
#define MAIN_FUNCTION_STACKMEMORY_LOCATION 0x90000 // edfined in switch_to_pm.asm

#endif