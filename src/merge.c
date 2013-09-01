#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <src/database.h>
#include <src/merge.h>

int merge_teams()
{
	for(int i = 0; i < db_end; i++) {
		match_t **matches = malloc(sizeof(match_t *)*128);
		int num_matches = get_nth_db_element(i)->num_matches;
		matches = get_nth_db_element(i)->matches;
		
		for(int j = 1; i + j < db_end;) {
			
			if(get_nth_db_element(i)->number ==
			   get_nth_db_element(i+j)->number) {
				
				memcpy(&matches[num_matches],
				       get_nth_db_element(i+j)->matches,
				       (sizeof(match_t)*get_nth_db_element(i+j)->num_matches));
				
				num_matches += get_nth_db_element(i+j)->num_matches;
				
				delete_nth_db_element(i+j);
			} else {
				j++; // only increment if we didn't replace
				     // (if we used delete_nth_db_element, the element was replaced
				     // and we need to test the element that now occupies the old one's spot)
			}
		}
		team_set_from_data(get_nth_db_element(i),
		                   get_nth_db_element(i)->number,
		                   get_nth_db_element(i)->name,
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

				if(strcmp(team->matches[i]->position, team->matches[i+j]->position)) {
					printf("Merge conflict in position (%s vs %s), assuming second.\n",
					       team->matches[i]->position,
					       team->matches[i+j]->position);
					strcpy(team->matches[i]->position, team->matches[i+j]->position);
				}
				
				if(strcmp(team->matches[i]->notes, team->matches[i+j]->notes)) {
					char new_notes[256];
					printf("Merge conflict in notes, concatenating.\n");
					strcpy(new_notes, team->matches[i]->notes);
					strcat(new_notes, "\n");
					strcat(new_notes, team->matches[i+j]->notes);
					strcpy(team->matches[i]->notes, new_notes);
				}

				team->matches[i+j] = team->matches[team->num_matches - 1];
				team->num_matches--;
			} else {
				j++; // see above reasoning in merge_teams
			}
		}
	}
	return 0;
}
