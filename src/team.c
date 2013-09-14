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

#include <stdlib.h>
#include <string.h>

#include <src/team.h>

/* Simply creates, allocates, and returns an empty team structure (pointers inside may not be initialized!) */

team_t *team_new()
{ team_t *ret = malloc(sizeof(team_t));
	return ret;
}

/* Creates a new team struct and populates it with the arguments given as the data */

team_t *team_new_from_data(unsigned int number, char name[128], match_t **matches, unsigned int num_matches)
{ team_t *ret = team_new();
	team_set_from_data(ret, number, name, matches, num_matches);
	
	return ret;
}

team_t *team_new_from_data_sorted(unsigned int number, char name[128], match_t **matches, unsigned int num_matches, int value)
{ team_t *ret = team_new();
	team_set_from_data(ret, number, name, matches, num_matches);
	ret->value = value;

	return ret;
}


int team_set_from_data(team_t *in, unsigned int number, char name[128], match_t **matches, unsigned int num_matches)
{
	/* TODO: add validations, perhaps detect if stuff isn't allocated and call functions to allocate it [matches ptr] */

	in->number = number;
	strcpy(in->name, name);
	in->matches = matches;
	in->num_matches = num_matches;

	return 0;
}

int team_free();
