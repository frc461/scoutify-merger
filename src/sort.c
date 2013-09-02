#include <stdlib.h>
#include <stdio.h>

#include <src/sort.h>

int find_value(team_t *team)
{
	return team->number;
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

