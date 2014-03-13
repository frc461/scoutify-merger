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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <src/sort.h>
#include <src/match.h>

double find_value(team_t *team)
{	double ret;

	double total_value_in_comp = 0.0;

	for(unsigned int mn = 0; mn < team->num_matches; mn += 1) {
		total_value_in_comp += match_get_team_value(team->matches[mn]);
	}

	ret = total_value_in_comp / team->num_matches;

	return ret;
}

int set_sort_value(team_t *team)
{
	team->value = find_value(team);
	return 0;
}

int team_compare(const void *a, const void *b)
{
	return (*(const team_t **)b)->value - (*(const team_t **)a)->value;
}

int match_number_to_sort_value(const char *match_number)
{	int ret = 0;

	if((match_number[0] == 'p') && (match_number[1] == 'm')) {
		ret = atoi(&(match_number[2])) - 100;
	}
	else if((match_number[0] == 'q') && (match_number[1] == 'm')) {
		ret = atoi(&(match_number[2]));
	}
	else if((match_number[0] == 'q') && (match_number[1] == 'f')) {
		ret = atoi(&(match_number[4])) + 100;
	}
	else if((match_number[0] == 's') && (match_number[1] == 'f')) {
		ret = atoi(&(match_number[4])) + 200;
	}
	else if((match_number[0] == 'f')) {
		ret = atoi(&(match_number[3])) + 300;
	}

	printf("%s has value %i\nstrcmpqm = %i\n", match_number, ret, strcmp(match_number, "qm"));

	return ret;
}

int match_compare(const void *a, const void *b)
{
	const match_t *match_a = *(const match_t **)a;
	const match_t *match_b = *(const match_t **)b;

	int a_sort_value = match_number_to_sort_value(match_a->round);
	int b_sort_value = match_number_to_sort_value(match_b->round);

	return a_sort_value - b_sort_value;
}

int database_sort()
{
	for(int i = 0; database_get_nth_element(i); i++) {
		set_sort_value(database_get_nth_element(i));
	}
	qsort(_unrestricted_db_(),
	      _database_num_elements_(),
	      sizeof(team_t *),
	      team_compare);
	for(int i = 0; database_get_nth_element(i); i++) {
		qsort(database_get_nth_element(i)->matches,
		      database_get_nth_element(i)->num_matches,
		      sizeof(match_t *),
		      match_compare);
	}
	return 0;
}

