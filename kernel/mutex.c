#include "mutex.h"

mutex_t mutex_used[MAX_OVERALL_MUTEXES] = {[0 ... MAX_OVERALL_MUTEXES-1]={0,0}};
uint8_t total_mutexes = 0;

//trying to create a mutex, returning 0 if couldn't.
mutex_ptr create_mutex()
{
	int8_t free_mutex_location;
	if(tasks[currently_running_task_id].total_mutex_own == 3) //max  mutexes per process exceeded
		return SYS_CALL_ERR;
	free_mutex_location = find_free_mutex();
	if(free_mutex_location == INTERNAL_ERROR) //coudln't find a new mutex location
		return SYS_CALL_ERR;
	mutex_used[free_mutex_location].memory_location = MUTEX_MEMORY_LOCATION+free_mutex_location*sizeof(uint32_t); // calculating the memory location of the returned mutex
	total_mutexes++;// total mutexes going up
	return mutex_used[free_mutex_location].memory_location;
}

//returning place in mutex array for a free mutex to use, else returning error
int8_t find_free_mutex()
{
	if(total_mutexes == MAX_OVERALL_MUTEXES)
		return INTERNAL_ERROR; //max mutexes used in entire machine
	for (int8_t i=0;i<15;++i){
		if(mutex_used[i].memory_location == 0)
			return i;
	}
	return INTERNAL_ERROR; // couldn't find a free mutex.
}
