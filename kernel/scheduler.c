#include "scheduler.h"



void scheduler()
{
	uint8_t tmp_cur_tsk;
	if(currently_running_task_id == IDLE_TASK_ID || currently_running_task_id == IDLE_TASK_ID-1){//if the current task is the last/idle one
		currently_running_task_id = 0; //todo = needs to be the most priority one.
		tmp_cur_tsk = IDLE_TASK_ID-1;
	}else{
		tmp_cur_tsk = currently_running_task_id;
		currently_running_task_id++;
	}

	do{ // check all tasks
		if(tasks[currently_running_task_id].status == alive){ //if we got task ready to run - break.
			break;
		}
		if(tmp_cur_tsk == currently_running_task_id){ // we returned to the same task again - which means they are all waiting\terminated
			currently_running_task_id = IDLE_TASK_ID; // idle task
			break;
		}
		else{
			if (currently_running_task_id == LAST_USER_TASK_ID) // got to last task - return back
				currently_running_task_id = 0;
			else //didnt get to last task - check next.
				currently_running_task_id++;
		}
	}while(currently_running_task_id <= LAST_USER_TASK_ID);
}
