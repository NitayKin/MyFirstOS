#include "scheduler.h"



void scheduler()
{
    if (total_tasks > 0)
    {
		currently_running_task_id++;
    	while(currently_running_task_id < MAX_TASKS){ // check all tasks
			if(tasks[currently_running_task_id].status == alive){ //if we got task ready to run - break.
//			    print("XX",2);
//			    print_hex(&currently_running_task_id,1);
				break;
			}
	    	if (currently_running_task_id == MAX_TASKS-1){ // got to last task - return back
	    		currently_running_task_id = 0;
	    	}
			else {//dead or waiting - try next one
				currently_running_task_id++;
			}
    	}
    }
}
