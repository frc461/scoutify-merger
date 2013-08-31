#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <src/argument.h>

argument_t *_root_argument_ = NULL;

argument_t *_argument_new_()
{ argument_t *ret = malloc(sizeof(argument_t));
	return ret;
}

argument_t *argument_new_from_data(int argc, char *argv)
{ argument_t *ret = _argument_new_();

	argument_set_data(ret, argc, argv);
	
	return ret;
}

argument_t *argument_new_from_data_after_argument(int argc, char *argv, argument_t *argument)
{ argument_t *ret = argument_new_from_data(argc, argv);

	argument_insert_after_argument(argument, ret);
	
	return ret;
}

void argument_insert_after_argument(argument_t *argument, argument_t *to_insert)
{
	if(argument->next != NULL) {
		printf("insertion detected previous next @0x%x w/ parent @0x%x\n", argument->next, argument);
		printf("%4s(we'll make a copy and then insert that as the next of the insertion)\n", "");

		argument_t *previous_next = argument->next;
		argument->next = to_insert;
		argument->next->next = previous_next;
	}
	
	argument->next = to_insert;
}

void argument_set_data(argument_t *argument, int index, char *value)
{
	argument->value = value;
	argument->index = index;
}

argument_t *argument_get_last_in_linked_list()
{
	argument_t *i = _root_argument_;

	while(i->next != NULL)
		i = i->next;

	return i;
}

void argument_build_list_from_arguments(int argc, char *argv[])
{
	_root_argument_ = argument_new_from_data(0, argv[0]);
	
	for(int i = 1; i < argc; i += 1) {
		argument_t *new = argument_new_from_data_after_argument(i, argv[i], argument_get_last_in_linked_list());
	}
}

void argument_debug_list()
{

	printf("DEBUG ARGLIST:\n");
	argument_t *i = _root_argument_;
	
	while(i != NULL) {
		printf("%4si => { %d [@ 0x%x] \"%s\" }\n", "", i->index, i, i->value);
		i = i->next;
	}

	argument_t *last = argument_get_last_in_linked_list();
	
	printf("%8slast dtctd == { %d [@0x%x] \"%s\" }\n", "", last->index, last, last->value);
}

int argument_get_number_of_elements_in_list()
{ int ret = 0;
	argument_t *i = _root_argument_;

	while(i != NULL) {
		ret += 1;
		i = i->next;
	}

	return ret;
}

argument_t **argument_get_array_of_argument_pointers_from_system_list()
{ argument_t **ret = malloc(sizeof(argument_t *) * argument_get_number_of_elements_in_list());
	unsigned int counter = 0;
	argument_t *i = _root_argument_;
	
	while(i != NULL) {
		ret[counter] = i;
		counter += 1;
		i = i->next;
	}
	
	return ret;
}

argument_execution_choices_t *argument_execution_choices_new()
{ argument_execution_choices_t *ret = malloc(sizeof(argument_execution_choices_t));
	return ret;
}

argument_execution_choices_t *argument_execution_choices_from_system_list()
{ argument_execution_choices_t *ret = argument_execution_choices_new();

	printf("%d arguments in system list, building execution choices structure from that\n", argument_get_number_of_elements_in_list());

	int argumentcount = argument_get_number_of_elements_in_list();
	argument_t **arguments = argument_get_array_of_argument_pointers_from_system_list();

	ret->in_file_definition_index = 0;
	ret->out_file_definition_index = 0;

	for(int i = 0; i < argumentcount; i += 1) {
		printf("[%d @ 0x%x] is \"%s\"\n", i, arguments[i], arguments[i]->value);
	}

	for(int i = 0; i < argumentcount; i += 1) {
		for(int j = 0; j < strlen(arguments[i]->value); j += 1) {
			arguments[i]->value[j] = tolower(arguments[i]->value[j]);
		}
	}
	
	for(int i = 0; i < argumentcount; i += 1) {
		if(arguments[i]->value[1] == 'f' &&
		   arguments[i]->value[2] == '=') {
			if(arguments[i]->value[0] == 'i') {
				ret->in_file = arguments[i]->value;
				ret->in_file_definition_index = i;
			} else if(arguments[i]->value[0] == 'o') {
				ret->out_file = arguments[i]->value;
				ret->out_file_definition_index = i;
			} else {
				printf("err: malformed argument: %s (skipping)!\n", arguments[i]->value);
			}
		}
	}
	
	return ret;
}
