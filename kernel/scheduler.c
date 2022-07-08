#include "scheduler.h"

void scheduler()
{
    if (total_tasks > 0)
    {
        for(int i=0;i<256;++i) // search for the next task to run
        {
            if( (i != currently_running_task_id) && (tasks[i].alive==true))
            {
                currently_running_task_id = i;
                break;
            }
        }
    }
}