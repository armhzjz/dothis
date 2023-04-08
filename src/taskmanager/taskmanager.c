#include <stdlib.h>
#include <string.h>
#include "taskmanager.h"

task_t *create_task(char todo[], time_t due_date) {
    if (/* todo is empty...*/
        !strcmp((const char *)"", (const char *)todo))
            return NULL;
    task_t * t = malloc(sizeof(task_t));
    if (/* memory allocation failed... */
        !t)
        return NULL;
    t->todo = todo;
    time_t now = time(NULL); /* get the time of right now */
    t->due_date = (due_date > now) ? due_date : 0;
    t->bell = (bool) t->due_date; /* by default, bell is set to true if due date is valid */
    return t;
}