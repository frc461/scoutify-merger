#include <stdio.h>
#include <stdlib.h>

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
