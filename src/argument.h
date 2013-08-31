#ifndef ARGUMENT_H
#define ARGUMENT_H

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

argument_t *argument_last_in_linked_list();

#endif
