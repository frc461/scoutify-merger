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
#include <stdio.h>

#include <src/sort.h>

int find_value(team_t *team)
{
	return team->num_matches;
}

int set_sort_value(team_t *team)
{
	team->value = find_value(team);
	return 0;
}

int compare(const void *a, const void *b)
{
	return (*(const team_t **)b)->value - (*(const team_t **)a)->value;
}

int database_sort()
{
	for(int i = 0; database_get_nth_element(i); i++) {
		set_sort_value(database_get_nth_element(i));
	}
	qsort(_unrestricted_db_(),
	      _database_num_elements_(),
	      sizeof(team_t *),
	      compare);
	return 0;
}

