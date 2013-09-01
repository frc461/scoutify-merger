#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <stdbool.h>

typedef struct argument {
	char *value;
	int index;
	
	struct argument *next;
} argument_t;

extern argument_t *_root_argument_;

argument_t *_argument_new_();
argument_t *argument_new_from_data(int argc, char *argv);
argument_t *argument_new_from_data_after_argument(int argc, char *argv, argument_t *argument);

void argument_set_data(argument_t *argument, int index, char *value);

void argument_insert_after_argument(argument_t *argument, argument_t *to_insert);
void argument_build_list_from_arguments(int argc, char *argv[]);

argument_t *argument_get_last_in_linked_list();
argument_t *argument_list_get_nth_element(int n);
argument_t **argument_get_array_of_argument_pointers_from_system_list();
int argument_get_number_of_elements_in_list();
void argument_debug_list();

char **argument_get_paths_from_list();

#endif
