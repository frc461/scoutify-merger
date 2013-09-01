#include <stdio.h>

#include <src/argument.h>
#include <src/database.h>
#include <src/display.h>
#include <src/file.h>

#include <src/main.h>

int main(int argc, char *argv[])
{
	argument_build_list_from_arguments(argc, argv);
	argument_debug_list();
	
	database_init();

	if(argc < 2) return 0;
	
	load_dot_scoutify(argv[1]);
	if(argc > 2) load_dot_scoutify(argv[2]);

	merge_teams();

	for(int i = 0; database_get_nth_element(i); i++) {
		merge_matches(database_get_nth_element(i));
	}

	database_sort();
	
	for(int i = 0; database_get_nth_element(i); i++) {
		printf("TEAM: %u\n", database_get_nth_element(i)->number);
		printf("num matches: %u\n", database_get_nth_element(i)->num_matches);
		for(int j = 0; j < database_get_nth_element(i)->num_matches; j++) {
			printf("Position: %s\n", database_get_nth_element(i)->matches[j]->position);
			printf("Round: %s\n", database_get_nth_element(i)->matches[j]->round);
			printf("Notes: %s\n", database_get_nth_element(i)->matches[j]->notes);
		}
	}

	database_display();
	
	return 0;
}
