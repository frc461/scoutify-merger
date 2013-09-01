#include <stdio.h>

#include <src/argument.h>
#include <src/database.h>
#include <src/file.h>

#include <src/main.h>

int main(int argc, char *argv[])
{
	argument_build_list_from_arguments(argc, argv);
	argument_debug_list();
	
	init_db();

	if(argc < 2) return 0;

	load_dot_scoutify(argv[1]);
	if(argc > 2) load_dot_scoutify(argv[2]);

	merge_teams();

	for(int i = 0; get_nth_db_element(i); i++) {
		merge_matches(get_nth_db_element(i));
	}

	sort_db();
	
	for(int i = 0; get_nth_db_element(i); i++) {
		printf("TEAM: %u\n", get_nth_db_element(i)->number);
		printf("num matches: %u\n", get_nth_db_element(i)->num_matches);
		for(int j = 0; j < get_nth_db_element(i)->num_matches; j++) {
			printf("Position: %s\n", get_nth_db_element(i)->matches[j]->position);
			printf("Round: %s\n", get_nth_db_element(i)->matches[j]->round);
			printf("Notes: %s\n", get_nth_db_element(i)->matches[j]->notes);
		}
	}

	return 0;
}
