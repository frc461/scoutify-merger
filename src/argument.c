/*
    Copyright Christopher Cooper and Kristofer Rye 2013

    This file is part of scoutify-merger.

    scoutify-merger is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    scoutify-merger is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with scoutify-merger.  If not, see <http://www.gnu.org/licenses/>.
*/

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

argument_t *_argument_new_from_data_(int argc, char *argv)
{ argument_t *ret = _argument_new_();

	_argument_set_data_(ret, argc, argv);
	
	return ret;
}

argument_t *_argument_new_from_data_after_argument_(int argc, char *argv, argument_t *argument)
{ argument_t *ret = _argument_new_from_data_(argc, argv);

	_argument_insert_after_argument_(argument, ret);
	
	return ret;
}

void _argument_insert_after_argument_(argument_t *argument, argument_t *to_insert)
{
	if(argument == NULL) {
		_root_argument_ = to_insert;
	} else {
		/* If we've already got a 'next' member in 'argument', and it's not NULL, then
		 * that means there's probably some other argument coming after the given argument.
		 */
		if(argument->next != NULL) {
			/* Warn the user (hardly ever happens because the only time this function should
			 * be called is by the system list generator and it does things nicely and in sequence)
			 */
			printf("insertion detected previous next @0x%x w/ parent @0x%x\n", argument->next, argument);
			printf("%4s(we'll make a copy and then insert that as the next of the insertion)\n", "");
			
			/* Make a copy of the previous 'next' member */
			argument_t *previous_next = argument->next;
			/* Then insert the given argument pointer. */
			argument->next = to_insert;
			/* Then set the next of the given argument pointer to be the copy. */
			argument->next->next = previous_next;
			return;
		} else {
			/* Otherwise, just set the next to be the next. */
			argument->next = to_insert;
		}
	}

}

void _argument_set_data_(argument_t *argument, int index, char *value)
{
	argument->value = value;
	argument->index = index;
}

argument_t *_argument_get_last_argument_in_system_list_()
{
	argument_t *i = _root_argument_;

	if(i == NULL)
		return i;
	
	while(i->next != NULL)
		i = i->next;

	return i;
}

void argument_build_system_list_from_arguments(int argc, char *argv[])
{
	/* We always should have argv[0], at the least */
	_root_argument_ = _argument_new_from_data_(0, argv[0]);
	
	for(int i = 1; i < argc; i += 1) {
		argument_t *new = _argument_new_from_data_after_argument_(i, argv[i], _argument_get_last_argument_in_system_list_());
	}
}

void argument_debug_system_list()
{

	printf("DEBUG ARGLIST:\n");
	argument_t *i = _root_argument_;
	
	while(i != NULL) {
		printf("%4si => { %d [@ 0x%x] \"%s\" }\n", "", i->index, i, i->value);
		i = i->next;
	}

	argument_t *last = _argument_get_last_argument_in_system_list_();
	
	printf("%8slast dtctd == { %d [@0x%x] \"%s\" }\n", "", last->index, last, last->value);
}

int argument_get_number_of_elements_in_system_list()
{ int ret = 0;
	/* Get an iterator, preset to the root argument */
	argument_t *i = _root_argument_;

	/*  Move the iterator to whatever the iterator's 'next' member is,
	 * until the iterator becomes null. Increment a counter.
	 */
	while(i != NULL) {
		ret += 1;
		i = i->next;
	}

	/* Return the counter. */
	return ret;
}

argument_t *argument_system_list_get_nth_element(int n)
{ argument_t *argument = _root_argument_;
	/* Counter to count up to n. */
	int c = 0;

	/* Loop while we still have some elements to continue through. */
	while(c < n) {
		/*  Make sure we're not setting our argument "iterator" to NULL
		 * (which is bad because segfaults >:[)
		 *
		 *  If the next is NULL (but we still have some more iterations
		 * to do because we haven't returned yet) then return the current
		 * argument, because at least that's some progress through the tree,
		 * and some progress is better than a segfault.
		 *
		 *  If the next isn't NULL, then traverse up it and set our argument
		 * iterator to the next.
		 */
		if(argument->next != NULL) {
			argument = argument->next;
		} else {
			return argument;
		}

		c += 1;
	}

	/* Return our iterator thing. */
	return argument;
}

argument_t **argument_get_array_of_argument_pointers_from_system_list()
{ argument_t **ret = malloc(sizeof(argument_t *) * argument_get_number_of_elements_in_system_list());
	/* A counter and an iterator. */
	unsigned int counter = 0;
	argument_t *i = _root_argument_;

	/* Iterate through the argument L.L. and generate the array of pointers.*/
	while(i != NULL) {
		ret[counter] = i;
		counter += 1;
		i = i->next;
	}
	
	return ret;
}

char **argument_get_argument_values_from_system_list()
{ char **ret = malloc(sizeof(char *) * argument_get_number_of_elements_in_system_list() - 1);
	/* Pretty simple iteration here. */
	for(int i = 1; i < argument_get_number_of_elements_in_system_list(); i += 1) {
		ret[i - 1] = argument_system_list_get_nth_element(i)->value;
	}
	
	return ret;
}
