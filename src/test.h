#ifndef TEST_H
#define TEST_H

#include <stdbool.h>

typedef struct test_hook_t {
	char *key;
	void (*hook_function)(void *);

	struct test_hook_t *next;
} test_hook_t;

extern test_hook_t *_test_hook_linked_list_;

test_hook_t *_test_hook_new_empty_();
void _test_hook_set_data_(test_hook_t *hook, char *key, void (*hook_function)(void *));

test_hook_t *_test_hook_new_(char *key, void (*hook_function)(void *));

unsigned int _test_hook_linked_list_get_number_of_elements_();
test_hook_t *_test_hook_linked_list_get_nth_element_(unsigned int n);
test_hook_t *_test_hook_linked_list_get_last_element_();
void _test_hook_linked_list_add_to_after_(test_hook_t *hook, test_hook_t *to_insert);

test_hook_t *test_hook_new_add(char *key, void (*hook_function)(void *));

bool test_hook_match_key(test_hook_t *hook_a, char *key_b);

void test_execute_all_hooks();
void test_execute_all_hooks_after(test_hook_t *hook);
void test_execute_all_hooks_after_matching_key(char *key);
void test_execute_all_hooks_before(test_hook_t *hook);
void test_execute_all_hooks_before_matching_key(char *key);

void _test_execute_hook_(test_hook_t *hook);

#ifdef RUN_TESTS

extern void *_test_callback_global_data_;

#endif

void test_callback_test_print(void *data);

#endif
