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
#include <string.h>

#include <src/database.h>
#include <src/merge.h>

int merge_teams()
{
	for(int i = 0; database_get_nth_element(i); i++) {
		match_t **matches = malloc(sizeof(match_t *)*128);
		int num_matches = database_get_nth_element(i)->num_matches;
		matches = database_get_nth_element(i)->matches;

		for(int j = 1; database_get_nth_element(i+j);) {

			if(database_get_nth_element(i)->number ==
			   database_get_nth_element(i+j)->number) {

				memcpy(&matches[num_matches],
				       database_get_nth_element(i+j)->matches,
				       (sizeof(match_t *)*database_get_nth_element(i+j)->num_matches));

				num_matches += database_get_nth_element(i+j)->num_matches;

				database_delete_nth_element(i+j);
			} else {
				j++; /*  only increment if we didn't replace (if we used
				      * database_delete_nth_element, the element was
				      * replaced and we need to test the element that now
				      * occupies the old one's spot)
				      */
			}
		}
		team_set_from_data(database_get_nth_element(i),
		                   database_get_nth_element(i)->number,
		                   database_get_nth_element(i)->name,
		                   matches,
		                   num_matches);
	}
	return 0;
}

int merge_matches(team_t *team)
{
	for(int i = 0; i < team->num_matches; i++) {
		for(int j = 1; (i + j) < team->num_matches;) {

			if(!strcmp(team->matches[i]->round, team->matches[i+j]->round)) {

				printf("Merging matches %u: %s and %u: %s\n",
				       i, team->matches[i]->round,
				       i+j, team->matches[i+j]->round);

				/* print_match(team->matches[i]); */
				/* print_match(team->matches[i+j]); */

				if(team->matches[i]->position != team->matches[i+j]->position) {
					printf("Merge conflict in position (%s vs %s), assuming second.\n",
					       position_int_to_string(team->matches[i]->position),
					       position_int_to_string(team->matches[i+j]->position));
					team->matches[i]->position = team->matches[i+j]->position;
				}

				if(strcmp(team->matches[i]->notes, team->matches[i+j]->notes)) {
					char new_notes[256];
					printf("Merge conflict in notes, concatenating.\n");
					strcpy(new_notes, team->matches[i]->notes);
					strcat(new_notes, "\n");
					strcat(new_notes, team->matches[i+j]->notes);
					strcpy(team->matches[i]->notes, new_notes);
				}

				/*
				 * WARNING! SHOULD BE BETTER!
				 * We should free up the extra space and stuff.
				 */
				team->matches[i+j] = team->matches[team->num_matches - 1];
				team->num_matches--;

			} else {
				j++; /* see above reasoning in merge_teams */
			}
		}
	}
	return 0;
}

int merge_all()
{
	/* printf("before merging\n"); */
	/* for(int i = 0; database_get_nth_element(i); i++) { */
	/* 	team_t *team = database_get_nth_element(i); */
	/* 	printf("team %i\n", team->number); */
	/* 	for(int j = 0; j < team->num_matches; j++) { */
	/* 		print_match(team->matches[j]); */
	/* 	} */
	/* } */

	merge_teams();

	/* printf("after team merging\n"); */
	/* for(int i = 0; database_get_nth_element(i); i++) { */
	/* 	team_t *team = database_get_nth_element(i); */
	/* 	printf("team %i\n", team->number); */
	/* 	for(int j = 0; j < team->num_matches; j++) { */
	/* 		print_match(team->matches[j]); */
	/* 	} */
	/* } */

	for(int i = 0; database_get_nth_element(i); i++) {
		merge_matches(database_get_nth_element(i));
	}

	return 0;
}
