#include "scheduler.h"



void scheduler()
{
	int index = 0;
	uint8_t next_priority_task = tasks_priority_order[index];
	while(next_priority_task!=MOCK_TASK){
		if(tasks[next_priority_task].status == alive){ //if we got task ready to run - break.
			currently_running_task_id = next_priority_task;
			return;
		}
		index++;
		next_priority_task = tasks_priority_order[index];
	}
	currently_running_task_id = IDLE_TASK_ID; //no task to run - run idle instead
}
