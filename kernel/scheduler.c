#include "scheduler.h"



void scheduler()
{
	int index = 0;
	int most_priority_task = tasks_priority_order[index];
	while(most_priority_task!=MOCK_TASK){
		if(tasks[most_priority_task].status == alive){ //if we got task ready to run - break.
			currently_running_task_id = most_priority_task;
			return;
		}
		index++;
		most_priority_task = tasks_priority_order[index];
	}
	currently_running_task_id = IDLE_TASK_ID;
}
