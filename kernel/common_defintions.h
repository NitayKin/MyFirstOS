#ifndef common_definitions_header
#define common_definitions_header


// memory definitions
#define DIRECTORY_TABLE_MEMORY_LOCATION 0xd00000
#define PAGE_TABLES_MEMORY_LOCATION 0xe00000
#define KERNEL_STACK_MEMORY_LOCATION 0x50000000 //interrupts - defined in the tss
#define USER_STACK_MEMORY_LOCATION 0x20000000
#define MALLOC_MEMORY_LOCATION 0x60000000 // memory for malloc functions.
#define MUTEX_MEMORY_LOCATION 0x70000000 // memory for mutex functions.
#define KERNEL_FUNCTION_MEMORY_LOCATION 0xd000
#define MAIN_FUNCTION_STACK_MEMORY_LOCATION 0x16000 // defined in switch_to_pm.asm
#define SCREEN_MMIO_LOCATION 0xb8000

//task definitions
#define KERNEL_TASK_CODE 0
typedef enum task_status{  alive=1,  waiting=2,  dead=0  } task_status;

//syscalls definitions
#define SYS_CALL_ERR 0
#define INTERNAL_ERROR -1

//mutex definitions
typedef uint32_t * mutex_ptr;

#endif
