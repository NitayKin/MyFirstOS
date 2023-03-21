#include "mutex.h"

mutex_t mutex_used[MAX_OVERALL_MUTEXES] = {[0 ... MAX_OVERALL_MUTEXES-1]={0,0}};
uint8_t total_mutexes = 0;

//trying to create a mutex, returning 0 if couldn't.
mutex_ptr create_mutex()
{
	int8_t free_mutex_index;
	free_mutex_index = find_free_mutex_index();
	if(free_mutex_index == INTERNAL_ERROR) //coudln't find a new mutex location
		return SYS_CALL_ERR;
	mutex_used[free_mutex_index].memory_location = MUTEX_MEMORY_LOCATION+free_mutex_index*sizeof(uint32_t); // calculating the memory location of the returned mutex
	total_mutexes++;// total mutexes going up
	return mutex_used[free_mutex_index].memory_location;
}

//trying to delete a mutex, returning status if successfull or not.
status delete_mutex(mutex_ptr mutex_memory_location)
{
	uint8_t mutex_index_inside_array = ((uint32_t)mutex_memory_location-MUTEX_MEMORY_LOCATION)/sizeof(uint32_t); // finding the lcoation of the mutex in array
	mutex_used[mutex_index_inside_array].task_id = 0;
	mutex_used[mutex_index_inside_array].memory_location =0;
	return SYS_CALL_SUCCESS;
}

//trying to lock the mutex, returning err if there was an error while trying to lock it
status lock_mutex(mutex_ptr mutex_memory_location)
{
	uint8_t mutex_index_inside_array = ((uint32_t)mutex_memory_location-MUTEX_MEMORY_LOCATION)/sizeof(uint32_t); // finding the lcoation of the mutex in array
	uint8_t total_mutex_owned_cur_task = tasks[currently_running_task_id].total_mutex_own; //the number of mutexes the current task is owning

	if(total_mutex_owned_cur_task==MAX_MUTEXES_PER_TASK || mutex_used[mutex_index_inside_array].task_id == currently_running_task_id){ //max 3 mutexes per task \ the task itself already locked it
		return SYS_CALL_ERR;
	}else{
		if(mutex_used[mutex_index_inside_array].task_id == 0){ // free mutex
			mutex_used[mutex_index_inside_array].task_id = currently_running_task_id;
			tasks[currently_running_task_id].mutex_own[total_mutex_owned_cur_task] = mutex_memory_location;
			tasks[currently_running_task_id].total_mutex_own++;
			return SYS_CALL_SUCCESS;
		} else{ // the mutex is already locked by another task
			if(tasks[currently_running_task_id].mutex_wait != mutex_memory_location){ // the task is not already waiting for this mutex, update the waiting queue
				tasks[currently_running_task_id].mutex_wait = mutex_memory_location; //remembering the mutex memory location to wait
				tasks[currently_running_task_id].status = waiting; // the process is now waiting for the mutex - will not conitnue after calling to the scheduler
			}
			return SYS_CALL_ERR;
		}
	}
}

status unlock_mutex(mutex_ptr mutex_memory_location)
{
	uint8_t mutex_index_inside_array = ((uint32_t)mutex_memory_location-MUTEX_MEMORY_LOCATION)/sizeof(uint32_t); // finding the index of the mutex in global mutex array
	uint8_t mutex_index_task = find_mutex_index_inside_task(mutex_memory_location);// index of mutex isnide tasks own array

	if(mutex_index_task != INTERNAL_ERROR){ //only the owned task can unlock the mutex
		mutex_used[mutex_index_inside_array].task_id = 0;
		tasks[currently_running_task_id].mutex_own[mutex_index_task] = 0; //zeroing the former owned mutex
		tasks[currently_running_task_id].total_mutex_own--;
		for(int tmp_task_idx=0;tmp_task_idx<MAX_TASKS;tmp_task_idx++){ //releasing all the other tasks that are waiting for the mutex
			if(tasks[tmp_task_idx].mutex_wait == mutex_memory_location){ //the checked task is waiting for this freed mutex
				tasks[tmp_task_idx].mutex_wait = 0;
				tasks[tmp_task_idx].status = alive;
			}
		}
		return SYS_CALL_SUCCESS;
	}
		return SYS_CALL_ERR;
}

//returning index in mutex array for a free mutex to use, else returning error
status find_free_mutex_index()
{
	if(total_mutexes == MAX_OVERALL_MUTEXES)
		return INTERNAL_ERROR; //max mutexes used in entire machine
	for (int8_t index=0;index<MAX_OVERALL_MUTEXES;++index){ //find first location of free mutex
		if(mutex_used[index].memory_location == 0)
			return index;
	}
	return INTERNAL_ERROR; // couldn't find a free mutex.
}


//returning the index inside the current tasks own mutex array, else returning INTERNAL_ERROR
int8_t find_mutex_index_inside_task(mutex_ptr mutex_memory_location)
{
	for (int8_t tmp_ind = 0; tmp_ind<MAX_MUTEXES_PER_TASK;tmp_ind++){ // running on all mutex indexes
		if(tasks[currently_running_task_id].mutex_own[tmp_ind] == mutex_memory_location)
			return tmp_ind;
	}
	return INTERNAL_ERROR;
}
