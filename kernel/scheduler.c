#include "scheduler.h"



void scheduler()
{
	uint8_t tmp_cur_tsk = currently_running_task_id;
    if (total_tasks > 0)
    {
		currently_running_task_id++;
    	while(currently_running_task_id < MAX_TASKS){ // check all tasks
			if(tasks[currently_running_task_id].status == alive){ //if we got task ready to run - break.
				break;
			}
	    	if (currently_running_task_id == MAX_TASKS-1){ // got to last task - return back
	    		currently_running_task_id = 0;
	    	}
			else {//dead or waiting - try next one
				if(tmp_cur_tsk == currently_running_task_id){ // we returned to the same task again - which means they are all waiting\terminated
					break; // let the next scheduler call to pick a task, when one of tasks wil return to be alive.
				}
				currently_running_task_id++;
			}
    	}
    }
}
