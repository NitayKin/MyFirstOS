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
	uint8_t total_mutex_waiting_cur_task = tasks[currently_running_task_id].total_mutex_wait; //the number of mutexes the current task is waiting for
	uint8_t total_mutex_owned_cur_task = tasks[currently_running_task_id].total_mutex_own; //the number of mutexes the current task is owning

	if(total_mutex_owned_cur_task==MAX_MUTEXES_PER_TASK || mutex_used[mutex_index_inside_array].task_id == currently_running_task_id){ //max 3 mutexes per task \ the task itself already locked it
		print("nah",3);
		print_hex(&total_mutex_owned_cur_task,1);
		print_hex(&mutex_used[mutex_index_inside_array].task_id,1);
		print_hex(&currently_running_task_id,1);
		return SYS_CALL_ERR;
	}else{
		if(mutex_used[mutex_index_inside_array].task_id == 0){ // free mutex
			mutex_used[mutex_index_inside_array].task_id = currently_running_task_id;
			tasks[currently_running_task_id].mutex_own[total_mutex_owned_cur_task] = mutex_memory_location;
			tasks[currently_running_task_id].total_mutex_own++;
			return SYS_CALL_SUCCESS;
		} else{ // the mutex is already locked by another task
			if(task_already_wait_for_mutex(mutex_memory_location) == INTERNAL_ERROR){ // the task is not waiting for this mutex, update the waiting queue
				tasks[currently_running_task_id].mutex_wait[total_mutex_waiting_cur_task] = mutex_memory_location; //remembering the mutex memory location to wait
				tasks[currently_running_task_id].total_mutex_wait++;//increasing number of mutexes waiting
				tasks[currently_running_task_id].status = waiting; // the process is now waiting for the mutex - will not conitnue after calling to the scheduler
			}
			return SYS_CALL_ERR;
		}
	}
}

status unlock_mutex(mutex_ptr mutex_memory_location)
{
	uint8_t mutex_index_inside_array = ((uint32_t)mutex_memory_location-MUTEX_MEMORY_LOCATION)/sizeof(uint32_t); // finding the index of the mutex in array
	uint8_t total_mutex_waiting_cur_task = tasks[currently_running_task_id].total_mutex_wait; //the number of mutexes the current task is waiting for
	uint8_t total_mutex_owned_cur_task = tasks[currently_running_task_id].total_mutex_own; //the number of mutexes the current task is owning

	if(mutex_used[mutex_index_inside_array].task_id == currently_running_task_id){ //only the owned task can unlock the mutex
		mutex_used[mutex_index_inside_array].task_id = 0;
		tasks[currently_running_task_id].mutex_own[total_mutex_owned_cur_task] = 0; //zeroing the index of the memory location of the former mutex location
		tasks[currently_running_task_id].total_mutex_own--; //decreasing mutex used
		for(int tmp_task_idx=0;tmp_task_idx<MAX_TASKS;tmp_task_idx++){ //releasing all the other tasks that are waiting for the mutex
			for(int tmp_wait_mut_idx=0;tmp_wait_mut_idx<MAX_MUTEXES_PER_TASK;++tmp_wait_mut_idx){ //checking all mutexes waiting per task
				if(tasks[tmp_task_idx].mutex_wait[tmp_wait_mut_idx] == mutex_memory_location){ //the task is waiting for this mutex
					tasks[tmp_task_idx].mutex_wait[tmp_wait_mut_idx] = 0;
					tasks[tmp_task_idx].total_mutex_wait--;
					if(tmp_wait_mut_idx == 0) //if this is the last mutex the task is waiting - also make the task alive
						tasks[tmp_task_idx].status = alive;
				}
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

status task_already_wait_for_mutex(mutex_ptr mutex_memory_location)
{
	for(int tmp_wait_mut_idx=0;tmp_wait_mut_idx<MAX_MUTEXES_PER_TASK;++tmp_wait_mut_idx){ //checking all mutexes waiting
		if(tasks[currently_running_task_id].mutex_wait[tmp_wait_mut_idx] == mutex_memory_location)
			return INTERNAL_SUCCESS; //the task is already waiting for the mutex
	}
	return INTERNAL_ERROR;
}
