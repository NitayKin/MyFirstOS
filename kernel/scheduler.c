#include "scheduler.h"

void scheduler()
{
    if (total_tasks > 0)
    {
        if(tasks[++currently_running_task_id].alive != true) // simple - just go one by one and return to 0 if finished
            currently_running_task_id=0;
    }
}