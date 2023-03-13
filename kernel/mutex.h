#ifndef mutex_header
#define mutex_header

#include <stdint.h> //for type definitions
#include "common_defintions.h"
#include "tasks.h" // to link between mutex and task

#define MAX_OVERALL_MUTEXES 15

typedef struct{
	mutex_ptr memory_location; // the memory location of the mutex.
	uint32_t task_id; // the id of the owned task.
}mutex_t;

extern mutex_t mutex_used[MAX_OVERALL_MUTEXES]; // list of used mutexes
extern uint8_t total_mutexes; // how many mutexes are in use

mutex_ptr create_mutex(void);
status delete_mutex(mutex_ptr);
status lock_mutex(mutex_ptr);
status unlock_mutex(mutex_ptr);
status find_free_mutex(void);

#endif
