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

#include <src/match.h>

/*
 * Simply creates, allocates, and returns an empty match structure (pointers inside may not be initialized!)
 */
match_t *match_new()
{ match_t *ret = malloc(sizeof(match_t));
	return ret;
}
/*
 * Creates a new match struct and populates it with the arguments given as the data
 */
match_t *match_new_from_data(char position[4], char round[16], char notes[256])
{ match_t *ret = match_new();

	/*
	 * TODO: add validations, perhaps detect if stuff isn't allocated and call functions to allocate it [matches ptr]
	 */
	
	strcpy(ret->position, position);
	strcpy(ret->round, round);
	strcpy(ret->notes, notes);

	return ret;
}

int match_set_from_data(match_t *in, char position[4], char round[16], char notes[256])
{
	strcpy(in->position, position);
	strcpy(in->round, round);
	strcpy(in->notes, notes);

	return 0;
}

int match_free();
