#include <src/sort.h>
#include <stdlib.h>

int find_value(const team_t *team) {
	return team->number;
}

int set_sort_value(team_t *team) {
	team->number = find_value(team);
	return 0;
}

int compare(const void *a, const void *b) {
	return find_value(a) - find_value(b);
}

int sort_db() {
	for(int i = 0; get_nth_db_element(i); i++) {
		set_sort_value(get_nth_db_element(i));
	}
	qsort(unrestricted_db(),
	      num_db_elements(),
	      sizeof(team_t *),
	      compare);
}

