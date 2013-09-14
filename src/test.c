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

unsigned int _test_hook_linked_list_get_number_of_elements_()
{ unsigned int ret = 0;
	test_hook_t *iterator = _test_hook_linked_list_;

	while(iterator != NULL) {
		ret += 1;
		iterator = iterator->next;
	}

	return ret;
}

test_hook_t *_test_hook_linked_list_get_nth_element_(unsigned int n)
{ test_hook_t *iterator = _test_hook_linked_list_;
	unsigned int counter = 0;

	while(counter < n) {
		if(iterator->next != NULL) {
			iterator = iterator->next;
		} else {
			return iterator;
		}

		counter += 1;
	}

	return iterator;
}

test_hook_t *_test_hook_linked_list_get_last_element_()
{ test_hook_t *iterator = _test_hook_linked_list_;

	if(iterator == NULL)
		return iterator;

	while(iterator->next != NULL)
		iterator = iterator->next;

	return iterator;
}

void _test_hook_linked_list_add_to_after_(test_hook_t *hook, test_hook_t *to_insert)
{
	if(hook == NULL) {
		_test_hook_linked_list_ = to_insert;
	} else {
		if(hook->next != NULL) {
			test_hook_t *previous_next = hook->next;
			hook->next = to_insert;
			hook->next->next = previous_next;
		} else {
			hook->next = to_insert;
		}
	}
}

test_hook_t *test_hook_new_add(char *key, void (*hook_function)(void *))
{ test_hook_t *ret = _test_hook_new_(key, hook_function);

	_test_hook_linked_list_add_to_after_(_test_hook_linked_list_get_last_element_(), ret);

	return ret;
}

bool test_hook_match_key(test_hook_t *hook_a, char *key_b);

void test_execute_all_hooks()
{
	test_hook_t *iterator;
	for(unsigned int i = 0; i < _test_hook_linked_list_get_number_of_elements_(); i += 1) {
		iterator = _test_hook_linked_list_get_nth_element_(i);

		printf("Executing hook with key: %s\n", iterator->key);
		_test_execute_hook_(iterator);
	}
		
}

void test_execute_all_hooks_after(test_hook_t *hook);
void test_execute_all_hooks_after_matching_key(char *key);
void test_execute_all_hooks_before(test_hook_t *hook);
void test_execute_all_hooks_before_matching_key(char *key);

void _test_execute_hook_(test_hook_t *hook)
{
	hook->hook_function(_test_callback_global_data_);
}

#ifdef RUN_TESTS

void *_test_callback_global_data_ = NULL;

#endif

void test_callback_test_print(void *data)
{
#ifdef RUN_TESTS
	printf("%s\n", (char *)_test_callback_global_data_);
#else
	printf("%s\n", (char *)data);
#endif
}
