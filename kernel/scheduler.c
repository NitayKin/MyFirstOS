#include "scheduler.h"

void scheduler()
{
    if (total_tasks > 0)
    {
		currently_running_task_id++;
    	while(currently_running_task_id <= total_tasks){ // keep running untill finding a new task to run
			if(tasks[currently_running_task_id].status == alive) //if we got task ready to run - break.
					break;
	    	if (currently_running_task_id == total_tasks){ // got to last task - return back
	    		currently_running_task_id = 0;
	    	}
			else {//dead or waiting - try next one
				currently_running_task_id++;
			}
    	}
    }
}
