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

//trying to delete a mutex, returning status if successfull or not.
status delete_mutex(mutex_ptr mutex_memory_location)
{
	uint8_t mutex_place_inside_array = ((uint32_t)mutex_memory_location-MUTEX_MEMORY_LOCATION)/sizeof(uint32_t); // finding the lcoation of the mutex in array
	if(mutex_used[mutex_place_inside_array].task_id == currently_running_task_id){ // only if the ownership of the mutex is on the current task
		mutex_used[mutex_place_inside_array].task_id = 0;
		mutex_used[mutex_place_inside_array].memory_location =0;
		return SYS_CALL_SUCCESS;
	}
	return SYS_CALL_ERR;
}


status lock_mutex(mutex_ptr mutex_memory_location)
{
	uint8_t mutex_place_inside_array = ((uint32_t)mutex_memory_location-MUTEX_MEMORY_LOCATION)/sizeof(uint32_t); // finding the lcoation of the mutex in array
	uint8_t total_mutex_waiting_cur_task = tasks[currently_running_task_id].total_mutex_wait; //the number of mutexes the current task is waiting for
	uint8_t total_mutex_owned_cur_task = tasks[currently_running_task_id].total_mutex_own; //the number of mutexes the current task is owning

	if((mutex_used[mutex_place_inside_array].task_id == 0)||(mutex_used[mutex_place_inside_array].task_id == currently_running_task_id)){ // free mutex/already used mutex by same task - can lock it
		if(total_mutex_owned_cur_task==MAX_MUTEXES_PER_TASK) //max 3 mutexes per task
			return SYS_CALL_ERR;
		mutex_used[mutex_place_inside_array].task_id = currently_running_task_id;
		mutex_used[mutex_place_inside_array].memory_location =mutex_memory_location;
		tasks[currently_running_task_id].mutex_own[total_mutex_owned_cur_task] = mutex_memory_location;
		tasks[currently_running_task_id].total_mutex_own++;
		return SYS_CALL_SUCCESS;
	} else{ // the mutex is already locked
		if(total_mutex_waiting_cur_task==MAX_MUTEXES_PER_TASK) //max 3 mutexes per task
			return SYS_CALL_ERR;
		tasks[currently_running_task_id].mutex_wait[total_mutex_waiting_cur_task] = mutex_memory_location; //remembering the mutex memory location to wait
		tasks[currently_running_task_id].total_mutex_wait++;//increasing number of mutexes waiting
		tasks[currently_running_task_id].status = waiting; // the process is now waiting for the mutex - will not conitnue after calling to the scheduler

		timer_ticks = 20;// force scheduling of next task
		return SYS_CALL_ERR;
	}
}

status unlock_mutex(mutex_ptr mutex_memory_location)
{
	uint8_t mutex_place_inside_array = ((uint32_t)mutex_memory_location-MUTEX_MEMORY_LOCATION)/sizeof(uint32_t); // finding the lcoation of the mutex in array
	uint8_t total_mutex_waiting_cur_task = tasks[currently_running_task_id].total_mutex_wait; //the number of mutexes the current task is waiting for
	uint8_t total_mutex_owned_cur_task = tasks[currently_running_task_id].total_mutex_own; //the number of mutexes the current task is owning

	if(mutex_used[mutex_place_inside_array].task_id == currently_running_task_id){ //only the owned task can unlock the mutex
		mutex_used[mutex_place_inside_array].task_id = 0;
		tasks[currently_running_task_id].mutex_own[total_mutex_owned_cur_task] = 0;
		tasks[currently_running_task_id].total_mutex_own--;
		for(int i=0;i<MAX_TASKS;i++){ //releasing all the othe tasks that are waiting for the mutex
			for(int j=0;j<MAX_MUTEXES_PER_TASK;++j){ //checking all mutexes waiting per task
				if(tasks[i].mutex_wait[j] == mutex_memory_location){ //the task is waiting for this mutex
					tasks[i].mutex_wait[j] = 0;
					tasks[i].total_mutex_wait--;
					if(j == 0) //if this is the last mutex the task is waiting - also make the task alive
						tasks[i].status = alive;
				}
			}
		}
		return SYS_CALL_SUCCESS;
	}
		return SYS_CALL_ERR;
}

//returning place in mutex array for a free mutex to use, else returning error
status find_free_mutex()
{
	if(total_mutexes == MAX_OVERALL_MUTEXES)
		return INTERNAL_ERROR; //max mutexes used in entire machine
	for (int8_t i=0;i<15;++i){ //find first location of free mutex
		if(mutex_used[i].memory_location == 0)
			return i;
	}
	return INTERNAL_ERROR; // couldn't find a free mutex.
}
