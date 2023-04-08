#ifndef _DATAMODEL_
#define _DATAMODEL_

#include <time.h>
#include <stdbool.h>

typedef struct task {
    char *todo;
    time_t due_date;
    char *comments;
    bool bell;
    char *parent_list_id;
    struct task *next_task;
    struct task *last_task;
} task_t;

typedef struct todo_list {
    char *list_id;
    char *todo_list_name;
    time_t creation_time;
    time_t list_due_date;
    unsigned int tasks_in_list_cntr;
    task_t *tasks;
} todo_list_t;


#endif
