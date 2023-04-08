#include <stdlib.h>
#include "unity/unity.h"
#include "taskmanager_testing.h"
#include "taskmanager.h"
#include "datamodel.h"

void setUp(void) {}
void tearDown() {}

void test_create_task_no_todo(void) {
    task_t *t = create_task("", 0);
    TEST_ASSERT_EQUAL_PTR(NULL, t);
}

void test_create_task_duedate_zero(void) {
    task_t *t = create_task("nice task", 0);
    TEST_ASSERT_EQUAL_INT64((long int) 0, (long int) t->due_date);
    TEST_ASSERT_EQUAL_CHAR(0x00, t->bell);
    free(t);
}

void test_create_task_duedate_yesterday(void){
    time_t t_yesterday = time(NULL);
    struct tm tm = *localtime(&t_yesterday);
    tm.tm_mday--;
    t_yesterday = mktime(&tm);
    task_t *t = create_task("nice task", t_yesterday);
    TEST_ASSERT_EQUAL_INT64((long int) 0, (long int) t->due_date);
    TEST_ASSERT_EQUAL_CHAR(0x00, t->bell);
    free(t);
}

void test_create_task_duedate_tomorrow(void) {
    time_t t_tomorrow = time(NULL);
    struct tm tm = *localtime(&t_tomorrow);
    tm.tm_mday++;
    t_tomorrow = mktime(&tm);
    task_t *t = create_task("nice task", t_tomorrow);
    TEST_ASSERT_EQUAL_INT64((long int)t_tomorrow , (long int) t->due_date);
    TEST_ASSERT_EQUAL_CHAR(0x01, t->bell);
    free(t);
}

int main(void) {
    RUN_TEST(test_create_task_no_todo);
    RUN_TEST(test_create_task_duedate_zero);
    RUN_TEST(test_create_task_duedate_yesterday);
    RUN_TEST(test_create_task_duedate_tomorrow);
    return UnityEnd();
}