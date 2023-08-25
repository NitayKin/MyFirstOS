#ifndef user_tasks_header
#define user_tasks_header

#include <stdint.h> //for type definitions
#include "../kernel/user_system_calls.h"
#include "../kernel/common_defintions.h"

void main_user_task();
void increment_global_task();
void print_global_task();

#endif
