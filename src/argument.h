/*
    Copyright Christopher Cooper and Kristofer Rye 2013

    This file is part of scoutify-hub.

    scoutify-hub is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    scoutify-hub is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with scoutify-hub.  If not, see <http://www.gnu.org/licenses/>.
*/

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
argument_t *_argument_new_from_data_(int argc, char *argv);
argument_t *_argument_new_from_data_after_argument_(int argc, char *argv, argument_t *argument);

void _argument_set_data_(argument_t *argument, int index, char *value);

void _argument_insert_after_argument_(argument_t *argument, argument_t *to_insert);
void argument_build_system_list_from_arguments(int argc, char *argv[]);

argument_t *_argument_get_last_argument_in_system_list_();
argument_t *argument_system_list_get_nth_element(int n);
argument_t **argument_get_array_of_argument_pointers_from_system_list();
int argument_get_number_of_elements_in_system_list();
void argument_debug_system_list();

char **argument_get_argument_values_from_system_list();

#endif
