#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <src/test.h>

test_hook_t *_test_hook_linked_list_ = NULL;

test_hook_t *_test_hook_new_empty_()
{ test_hook_t *ret = malloc(sizeof(test_hook_t));
	return ret;
}

void _test_hook_set_data_(test_hook_t *hook, char *key, void (*hook_function)(void *))
{
	hook->key = malloc(strlen(key) * sizeof(char));
	strcpy(hook->key, key);

	hook->hook_function = hook_function;
}

test_hook_t *_test_hook_new_(char *key, void (*hook_function)(void *))
{ test_hook_t *ret = _test_hook_new_empty_();

	_test_hook_set_data_(ret, key, hook_function);

	return ret;
}

unsigned int _test_hook_linked_list_get_number_of_elements_();
test_hook_t *_test_hook_linked_list_get_nth_element_(int n);
test_hook_t *_test_hook_linked_list_get_last_element_();
void _test_hook_linked_list_add_to_after_(test_hook_t *hook, test_hook_t *to_insert);

test_hook_t *test_hook_new_add(char *key, void (*hook_function)(void *));

bool test_hook_match_key(test_hook_t *hook_a, char *key_b);

void test_execute_all_hooks();
void test_execute_all_hooks_after(test_hook_t *hook);
void test_execute_all_hooks_after_matching_key(char *key);
void test_execute_all_hooks_before(test_hook_t *hook);
void test_execute_all_hooks_before_matching_key(char *key);

void test_execute_hook(test_hook_t *hook);
