#ifndef tasks_header
#define tasks_header
#include <stdint.h> //for type definitions
#include <stdbool.h> // for bool usage
#include "memory_locations_defintions.h"
#include "print.h"
#include "clock_interrupt.h"


typedef struct{
    bool alive;
    uint8_t id;
    uint32_t eax;
    uint32_t edx;
    uint32_t ecx;
    uint32_t esp;
    uint32_t eip;
    uint32_t ebp;
    uint32_t eflags;
} TaskDescription;

extern TaskDescription tasks[256];
extern uint8_t total_tasks;
extern uint8_t currently_running_task_id;
extern uint32_t check;

void create_dummy_task(void*);// should be an interrupt!
void create_task(void*);// should be an interrupt!
void delete_task();// should be an interrupt!
void get_task_by_id(TaskDescription*,uint8_t);
void print_tasks();
void print_task_id(uint8_t);

#endif