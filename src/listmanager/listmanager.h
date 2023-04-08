#ifndef _LISTMANAGER_
#define _LISTMANAGER_

#include <time.h>
#include "datamodel.h"

typedef enum {
    OK_R = 0,
    NOK_R = 1,
    ADD_TASK_NOK_R = 2,
    TASK_NOT_IN_LIST = 3,
    LIST_NOT_EMPTY = 4,
    LIST_IN_INCONSISTENT_STATE = 5,
    DUE_DATE_NOT_VALID = 6
} ERROR_RETURN_L;

todo_list_t *create_list(char list_name[], time_t);
ERROR_RETURN_L add_task_to_list(todo_list_t *, task_t *);
ERROR_RETURN_L change_list_name(todo_list_t *, char new_name[]);
ERROR_RETURN_L remove_task_from_list(todo_list_t *, task_t*);
ERROR_RETURN_L add_list_due_date(todo_list_t *, time_t);
ERROR_RETURN_L destroy_list(todo_list_t *);

#endif
