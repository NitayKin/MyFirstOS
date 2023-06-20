#ifndef tasks_header
#define tasks_header
#include <stdint.h> //for type definitions
#include <stdbool.h> // for bool usage
#include "print.h"
#include "common_defintions.h"
#include "timer.h"
#include "mutex.h"


typedef struct{
	task_status status;
    uint8_t id;
    uint8_t total_mutex_own; // how many mutexes the task owns
    mutex_ptr mutex_wait;
    mutex_ptr mutex_own[MAX_OWNED_MUTEX_PER_TASK]; // max 3 mutexes acquired
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t eip;
    uint32_t eflags;
    uint32_t ticks_to_wait;
    uint8_t base_priority;
    uint8_t inherited_priority; //should be equal to priority, unless higher priority task waiting for its mutex.
} task_description_t;

extern task_description_t tasks[MAX_USER_TASKS];
extern uint8_t total_tasks;
extern uint8_t currently_running_task_id;
extern uint32_t check;

status create_task(void*,uint8_t);// should be an interrupt!
void delete_task(void);// should be an interrupt!
int8_t find_empty_task_slot(void);
void release_all_task_mutexes(void);
void get_task_by_id(task_description_t*,uint8_t);
void print_tasks(void);
void print_task_id(uint8_t);
void idle_task(); // if all tasks sleep - this will run.


#endif
