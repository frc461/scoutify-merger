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

void argument_insert_after_argument(argument_t *argument, argument_t *to_insert);

void argument_set_data(argument_t *argument, int index, char *value);

argument_t *argument_get_last_in_linked_list();

void argument_build_list_from_arguments(int argc, char *argv[]);

void argument_debug_list();

int argument_get_number_of_elements_in_list();

argument_t **argument_get_array_of_argument_pointers_from_system_list();

typedef enum {
	AE_STEP_MERGE,
	AE_STEP_SORT,
	AE_STEP_WRITE,
	AE_STEP_DISPLAY,
	
	AE_STEP_MAX,
} argument_execution_step_t;

typedef struct argument_execution_choices {
	argument_execution_step_t start;
	argument_execution_step_t end;

	char *in_file;
	char *out_file;
} argument_execution_choices_t;

argument_execution_choices_t *argument_execution_choices_new();
argument_execution_choices_t *argument_execution_choices_from_system_list();

#endif
