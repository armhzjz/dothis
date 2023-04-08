#ifndef _TASKMANAGER_
#define _TASKMANAGER_

#include <time.h>
#include <stdbool.h>
#include "datamodel.h"

typedef enum {
    OK_R = 0
} ERROR_RETURN_T;

task_t *create_task(char[], time_t);
ERROR_RETURN_T modify_task_name(task_t *, const char *);
ERROR_RETURN_T add_task_due_date(task_t *, time_t);
ERROR_RETURN_T add_task_commet(task_t *, const char*);
ERROR_RETURN_T toggle_task_notification(task_t *, bool);


#endif