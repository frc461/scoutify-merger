#include <src/argument.h>

argument_t *_root_argument_ = argument_new();

argument_t *_argument_new_()
{ argument_t *ret = malloc(sizeof(argument_t));
	return ret;
}

argument_t *argument_new_from_data(int argc, char *argv)
{ argument_t *ret = _argument_new_();
	ret->value = argv;
	ret->argc = argc;

	return ret;
}

argument_t *argument_new_from_data_after_argument(int argc, char *argv, argument_t *argument)
{ argument_t *ret = argument_new_from_data(argc, argv);
	
}

void argument_insert_after_argument(argument_t *argument, argument_t *to_insert)
{
	if(argument->next != NULL) {
		printf("insertion detected previous next @0x%x w/ parent @0x%x\n", argument->next, argument);
		printf("%4s(we'll make a copy and then insert that as the next of the insertion)\n". "");

		argument_t *previous_next = argument->next;
		argument->next = to_insert;
		argument->next->next = previous_next();
		
	}
	argument->next = to_insert;
}

argument_t *argument_last_in_linked_list()
{
	argument_t *i = _root_argument_;

	while(i->next != NULL)
		i = i->next;

	return i;
}
