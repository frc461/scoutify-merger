#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <src/database.h>
#include <src/merge.h>

int merge_teams() {
	for(int i = 0; i < db_end; i++) {
		match_t **matches = malloc(sizeof(match_t *)*128);
		int num_matches = get_nth_db_element(i)->num_matches;
		matches = get_nth_db_element(i)->matches;
		for(int j = 1; i + j < db_end; j++) {
			if(get_nth_db_element(i)->number ==
			   get_nth_db_element(i+j)->number) {
				memcpy(&matches[num_matches],
				       get_nth_db_element(i+j)->matches,
				       (sizeof(match_t)*get_nth_db_element(i+j)->num_matches));
				num_matches += get_nth_db_element(i+j)->num_matches;
				delete_nth_db_element(i+j);
			}
		}
		team_set_from_data(get_nth_db_element(i), get_nth_db_element(i)->number, get_nth_db_element(i)->name, matches, num_matches);
	}
}
