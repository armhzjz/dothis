#include<stdlib.h>
#include "unity/unity.h"
#include "listmanager_testing.h"
#include "listmanager.h"
#include "datamodel.h"

void setUp(void) {}
void tearDown() {}


/* create list */
void test_create_list_without_name(void) {
    todo_list_t * l = create_list("", 0);
    TEST_ASSERT_EQUAL_PTR(NULL, l);
}

void test_create_list_with_name(void) {
    todo_list_t * l = create_list("list_name", 0);
    TEST_ASSERT_EQUAL_PTR(NULL, !l);
    free(l->list_id);
    free(l);
}

void test_create_list_creation_time_is_due_date(void) {
    todo_list_t * l = create_list("lname", 0);
    TEST_ASSERT_EQUAL_INT64((long int)l->creation_time, (long int)l->list_due_date);
    free(l->list_id);
    free(l);
}

void test_create_list_valid_due_date(void) {
    time_t t;
    struct tm tm;
    tm.tm_year = 2024-1900;
    tm.tm_mon = 12-1;
    tm.tm_mday = 23;
    tm.tm_hour = 21;
    tm.tm_min = 50;
    tm.tm_sec = 45;
    tm.tm_isdst = -1;
    t = mktime(&tm);
    todo_list_t * l = create_list("lname", t);
    TEST_ASSERT_NOT_EQUAL_INT64((long int)l->creation_time, (long int)l->list_due_date);
    TEST_ASSERT_EQUAL_INT(l->list_due_date, t);
    free(l->list_id);
    free(l);
}

/* add task to list */
void test_add_task_to_list_null_l_null_t(void) {
    ERROR_RETURN_L r = add_task_to_list(NULL, NULL);
    TEST_ASSERT_EQUAL_CHAR(NOK_R, r);
}

void test_add_task_to_list_null_t(void) {
    todo_list_t * l = create_list("test", 0);
    ERROR_RETURN_L r = add_task_to_list(l, NULL);
    TEST_ASSERT_EQUAL_CHAR(NOK_R, r);
    free(l->list_id);
    free(l);
}

// void test_add_task_to_list_null_t(void) { NEED A TASK!!!!!!
//     task_t * 
//     ERROR_RETURN_L r = add_task_to_list(NULL, NULL);
//     TEST_ASSERT_EQUAL_CHAR(NOK_R, r);
// }

/* change list name */
void test_change_list_name_null_l_empty_name(void) {
    ERROR_RETURN_L r = change_list_name(NULL, "");
    TEST_ASSERT_EQUAL_CHAR(NOK_R, r);
}

void test_change_list_name_null_l(void) {
    ERROR_RETURN_L r = change_list_name(NULL, "nice_name");
    TEST_ASSERT_EQUAL_CHAR(NOK_R, r);
}

void test_change_list_name_empty_name(void) {
    todo_list_t *l = create_list("nice_name", 0);
    ERROR_RETURN_L r = change_list_name(l, "");
    TEST_ASSERT_EQUAL_CHAR(NOK_R, r);
    free(l->list_id);
    free(l);
}
void test_change_list_name_success(void) {
    todo_list_t *l = create_list("nice_name", 0);
    ERROR_RETURN_L r = change_list_name(l, "nice_name");
    TEST_ASSERT_EQUAL_CHAR(OK_R, r);
    free(l->list_id);
    free(l);
}

/* destroy list */
void test_destroy_list_null_l(void) {
    ERROR_RETURN_L r = destroy_list(NULL);
    TEST_ASSERT_EQUAL_CHAR(NOK_R, r);
}

void test_destroy_list_not_empty(void) {
    todo_list_t *l = create_list("nice_name", 0);
    l->tasks_in_list_cntr = 19;
    l->tasks = (task_t *) malloc(sizeof(task_t));
    ERROR_RETURN_L r = destroy_list(l);
    TEST_ASSERT_EQUAL_CHAR(LIST_NOT_EMPTY, r);
    free(l->tasks);
    free(l->list_id);
    free(l);
}

void test_destroy_list_inconsistent_task_counter(void) {
    todo_list_t *l = create_list("nice_name", 0);
    l->tasks_in_list_cntr = 2;
    ERROR_RETURN_L r = destroy_list(l);
    TEST_ASSERT_EQUAL_CHAR(LIST_IN_INCONSISTENT_STATE, r);
    free(l->list_id);
    free(l);
}

void test_destroy_list_inconsistent_tasks_ptr(void) {
    todo_list_t *l = create_list("nice_name", 0);
    l->tasks_in_list_cntr = 0;
    l->tasks = (task_t *) malloc(sizeof(task_t));
    ERROR_RETURN_L r = destroy_list(l);
    TEST_ASSERT_EQUAL_CHAR(LIST_IN_INCONSISTENT_STATE, r);
    free(l->tasks);
    free(l->list_id);
    free(l);
}

/* add due date to list */
void test_add_list_due_date_null_list(void) {
    ERROR_RETURN_L r = add_list_due_date(NULL, 0);
    TEST_ASSERT_EQUAL_CHAR(NOK_R, r);
}

void test_add_list_due_date_remove_due_date(void) {
    todo_list_t *l = create_list("nice_name", 0);
    ERROR_RETURN_L r = add_list_due_date(l, 0);
    TEST_ASSERT_EQUAL_CHAR(OK_R, r);
    TEST_ASSERT_EQUAL_INT64((long int)l->creation_time, (long int)l->list_due_date);
    free(l->list_id);
    free(l);
}

void test_add_list_due_date_due_date_not_valid(void) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    tm.tm_year = 1980 - 1900;
    t = mktime(&tm);
    todo_list_t *l = create_list("nice_name", 0);
    ERROR_RETURN_L r = add_list_due_date(l, t);
    TEST_ASSERT_EQUAL_CHAR(DUE_DATE_NOT_VALID, r);
    free(l->list_id);
    free(l);
}

void test_add_list_due_date_success(void) {
time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    tm.tm_year = 2100 - 1900;
    t = mktime(&tm);
    todo_list_t *l = create_list("nice_name", 0);
    ERROR_RETURN_L r = add_list_due_date(l, t);
    TEST_ASSERT_EQUAL_CHAR(OK_R, r);
    TEST_ASSERT_EQUAL_INT64((long int)l->list_due_date, t);
    free(l->list_id);
    free(l);
}

int main(void) {
    UnityBegin("test/list_manager");
    RUN_TEST(test_create_list_without_name);
    RUN_TEST(test_create_list_with_name);
    RUN_TEST(test_create_list_creation_time_is_due_date);
    RUN_TEST(test_create_list_valid_due_date);
    RUN_TEST(test_add_task_to_list_null_l_null_t);
    RUN_TEST(test_add_task_to_list_null_t);
    // RUN_TEST(test_add_task_to_list_null_l);
    RUN_TEST(test_change_list_name_null_l_empty_name);
    RUN_TEST(test_change_list_name_null_l);
    RUN_TEST(test_change_list_name_empty_name);
    RUN_TEST(test_change_list_name_success);
    RUN_TEST(test_destroy_list_null_l);
    RUN_TEST(test_destroy_list_not_empty);
    RUN_TEST(test_destroy_list_inconsistent_task_counter);
    RUN_TEST(test_destroy_list_inconsistent_tasks_ptr);
    RUN_TEST(test_add_list_due_date_null_list);
    RUN_TEST(test_add_list_due_date_remove_due_date);
    RUN_TEST(test_add_list_due_date_due_date_not_valid);
    RUN_TEST(test_add_list_due_date_success);
    return UnityEnd();
}