#ifndef mutex_header
#define mutex_header

#include <stdint.h> //for type definitions
#include "common_defintions.h"
#include "tasks.h" // to link between mutex and task

typedef struct{
	mutex_ptr memory_location; // the memory location of the mutex.
	int8_t task_id; // the id of the owned task.(-1 means not initialized, 0 means free to lock, other number means the task is acquired it)
}mutex_t;

extern mutex_t mutex_used[MAX_OVERALL_MUTEXES]; // list of used mutexes
extern uint8_t total_mutexes; // how many mutexes are in use

mutex_ptr create_mutex(void);
status delete_mutex(mutex_ptr);
status lock_mutex(mutex_ptr);
status unlock_mutex(mutex_ptr);
status free_mutex_index_inside_global_array(void);
int8_t mutex_index_inside_task(mutex_ptr);
int8_t free_mutex_index_inside_task();
flag_t is_mutex_ready(uint8_t,uint8_t);

#endif
