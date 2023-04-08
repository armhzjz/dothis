#include<stdlib.h>
#include<string.h>
#include "listmanager.h"

#define RAND_STRING_SIZE 32


/* declaration of private functions */
static char *rand_string(char *str);


todo_list_t *create_list(char list_name[], time_t due_date) {
    /*  Create a new list using the name (for such list) that is
        passed as an argument to this function.
        Empty strings as list name are not allowed.
        Otherwise the list is created. Creation time and
        due date are set to the same time time, unless due_date argument
        is passed with a value different than 0 AND greater than
        the current time;
    */
    todo_list_t *l = (todo_list_t *) malloc(sizeof(todo_list_t));
    if ( /* if malloc was not successfull or if list name is an empty string... */
        !l || !strcmp((const char *)"", (const char *)list_name)) {
            if ((bool)l)
                free(l); /* free l - cannot create a list without name */
            return NULL;
    }
    /*  generate list id by first allocating the required memory for it,
        and then generating the random 32 long string and assign it to
        the allocated memory
    */
    l->list_id = (char *) malloc(sizeof(char) * RAND_STRING_SIZE);
    if (/* no memory were allocated... */
        !l->list_id)
            return NULL;
    rand_string(l->list_id);
    l->todo_list_name = list_name;
    l->creation_time = time(NULL);
    if (due_date != 0 && due_date > l->creation_time)
        l->list_due_date = due_date;
    else
        /*  creation_time = list_due_date means there
            is no due date for this list
        */
        l->list_due_date = l->creation_time;
    l->tasks_in_list_cntr = 0;
    /*  
        I think we should not allocate memory for a task when creating
        a list. The memory should be allocated when the task is created and
        then it should be assigend to this list, but the
        "tasks" pointer points only to the first element of the list.
        l->tasks = (task_t *) malloc(sizeof(task_t *));
    */
    l->tasks = NULL;
    return l; /* return pointer to the new list */
}

ERROR_RETURN_T add_task_to_list(todo_list_t *l, task_t *t) {
    if (/* if either list or task pointers are null... */
        !l || !t)
        return NOK_R;
    if (/* list is not empty ... */
        (bool) l->tasks_in_list_cntr) {
            /* 
                We need to know how many tasks belong to this list.
                I case the linked list of tasks is brocken, we might go
                through the "list" endlessly, potentially  causing the 
                application to either hang or to fall into an undefined
                behavior. 
            */
            unsigned int aux_cntr = l->tasks_in_list_cntr;
            task_t *aux_t = l->tasks; /* get a hold of first task in list */
            for (; aux_t->next_task != aux_t;) {
                if (/*  we went through the total amount of tasks in this list
                        but we still didn't find the last element....
                    */ (bool) ! aux_cntr--)
                        /* retun NOK_R */
                        return NOK_R;
                /* follow the linked elements until reaching the last of them */
                aux_t = aux_t->next_task;
                
            }
            /*  found the last element in the list.
                Now we need to add a new element in that list.
            */
            aux_t->next_task = t;
            t->last_task = aux_t; /* link backwards to the last element in the list */
            t->next_task = t; /* this is the last element onf the linked list */
            t->parent_list_id = l->list_id; /* set task's parent list id to this list's id */
    }
    else {
        l->tasks = t;
        l->tasks->next_task = l->tasks->last_task = l->tasks; /* this is the last (and first) element of the linked list */
        t->parent_list_id = l->list_id; /* set task's parent list id to this list's id */
    }
    /* if the task was added to the list successfully, then increment the task counter */
    l->tasks_in_list_cntr++;
    return OK_R;
}

ERROR_RETURN_T change_list_name(todo_list_t *l, char new_name[]) {
    if (/* if either list or task pointers are null... */
        !l || !strcmp((const char *)"", (const char *) new_name))
        return NOK_R;
    l->todo_list_name = new_name;
    return OK_R;
}

ERROR_RETURN_T remove_task_from_list(todo_list_t *l, task_t* t) {
    if (/* if either list or task pointers are null... */
        !l || !t)
        return NOK_R;
    if ( /* list is empty ... */
        (bool) !l->tasks_in_list_cntr)
            return OK_R; /* return OK */
    /* sanity checks passed, now we need some variables to work with */
    task_t *t_aux = l->tasks; /* auxiliar variable pointing to first element on list */
    if (/* the task does not belong to this list...*/
        (bool) strcmp((const char *) t->parent_list_id, (const char *) l->list_id))
            return TASK_NOT_IN_LIST;
    /* remove the task from the list */
    for (unsigned int idx = 0;; idx++) {
        if (/* we found the task to be removed... */
            t_aux == t) {
                if (/* the task to remove is the first element in the list ...*/
                    (bool)!idx) {
                    if (/* the task to remove is also the last element in the list ...*/
                        t_aux->next_task == t_aux)
                            l->tasks = NULL;
                    else {
                        /*  the task to remove is the first element in the list,
                            but not the last one */
                        l->tasks->parent_list_id = ""; /* firs remove the parent id from this task */
                        l->tasks = l->tasks->next_task;
                        l->tasks->last_task = l->tasks; /* backward link is not set to the same (first) task */
                    }
                    /* decrement the counter of tasks in this list */
                    l->tasks_in_list_cntr--;
                    break; /* exit the loop */
                }
                else {
                    /* the task to remove is not the first element in the list */
                    t_aux->parent_list_id = ""; /* firs remove the parent id from this task */
                    t_aux->last_task->next_task = t_aux->next_task;
                    t_aux->next_task->last_task = t_aux->last_task;
                    l->tasks_in_list_cntr--;
                    break; /* exit the loop */
                }
        }
    }
    return OK_R;
}

ERROR_RETURN_T destroy_list(todo_list_t *l) {
    if (/* if either list or task pointers are null... */
        !l)
        return NOK_R;
    if (/* list is not empty...*/
        (bool)l->tasks_in_list_cntr && l->tasks != NULL)
        return LIST_NOT_EMPTY;
    else if (/* either element counter is bigger than zero
            or tasks pointer is not NULL (but only one these conditions is true) */
            (bool)l->tasks_in_list_cntr || l->tasks != NULL)
            return LIST_IN_INCONSISTENT_STATE;
    free(l->list_id); /* free allocated memory of list id */
    free(l); /* free the allocated memory of the list */
    return OK_R;
}

ERROR_RETURN_T add_list_due_date(todo_list_t *l, time_t due_date) {
    if (/* if either list or task pointers are null... */
        !l)
        return NOK_R;
    if (/* due_date is to be removed ...*/
        due_date == 0)
        l->list_due_date = l->creation_time;
    else if (/* due date is not zero and it is bigger than creation time */
            due_date > l->creation_time)
                l->list_due_date = due_date;
    else
        return DUE_DATE_NOT_VALID;
    return OK_R;
}

static char *rand_string(char *str) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890^!§$&/(){[]}=+#@|<>?";
    for (size_t n = 0; n < RAND_STRING_SIZE-1; n++) {
        int key = rand() % (int) (sizeof charset - 1);
        str[n] = charset[key];
    }
    str[RAND_STRING_SIZE-1] = '\0';
    return str;
}