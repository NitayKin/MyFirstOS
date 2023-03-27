#ifndef tasks_header
#define tasks_header
#include <stdint.h> //for type definitions
#include <stdbool.h> // for bool usage
#include "print.h"
#include "common_defintions.h"
#include "timer.h"


typedef struct{
	task_status status;
    uint8_t id;
    uint8_t total_mutex_own; // how many mutexes the task owns
    mutex_ptr mutex_wait;
    mutex_ptr mutex_own[3]; // max 3 mutexes acquired
    uint32_t eax;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t esp;
    uint32_t eip;
    uint32_t ebp;
    uint32_t eflags;
    uint32_t ticks_to_wait;
} task_description_t;

extern task_description_t tasks[MAX_TASKS];
extern uint8_t total_tasks;
extern uint8_t currently_running_task_id;
extern uint32_t check;

void create_task(void*);// should be an interrupt!
void delete_task();// should be an interrupt!
void get_task_by_id(task_description_t*,uint8_t);
void print_tasks();
void print_task_id(uint8_t);

#endif
