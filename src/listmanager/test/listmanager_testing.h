#ifndef LISTMANAGER_TEST_H
#define LISTMANAGER_TEST_H

/* create a list */
void test_create_list_without_name(void);
void test_create_list_with_name(void);
void test_create_list_creation_time_is_due_date(void);
void test_create_list_valid_due_date(void);

/* add task to list */
void test_add_task_to_list_null_l_null_t(void);
void test_add_task_to_list_null_t(void);
// void test_add_task_to_list_null_l(void);

/* change list name */
void test_change_list_name_null_l_empty_name(void);
void test_change_list_name_null_l(void);
void test_change_list_name_empty_name(void);
void test_change_list_name_success(void);

/* destroy list */
void test_destroy_list_null_l(void);
void test_destroy_list_not_empty(void);
void test_destroy_list_inconsistent_task_counter(void);
void test_destroy_list_inconsistent_tasks_ptr(void);

/* add due date to list */
void test_add_list_due_date_null_list(void);
void test_add_list_due_date_remove_due_date(void);
void test_add_list_due_date_due_date_not_valid(void);
void test_add_list_due_date_success(void);

#endif