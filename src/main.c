#include <stdio.h>

#include <src/argument.h>
#include <src/database.h>
#include <src/file.h>

#include <src/main.h>

int main(int argc, char *argv[])
{
	argument_build_list_from_arguments(argc, argv);
	argument_debug_list();
	argument_execution_choices_t *aect = argument_execution_choices_from_system_list();
	
	init_db();
	if(argc < 2) return 0;

	load_dot_scoutify(argv[1]);

	for(int i = 0; get_nth_db_element(i); i++) {
		printf("TEAM: %u\n", get_nth_db_element(i)->number);
		for(int j = 0; get_nth_db_element(i)->matches[j]; j++) {
			printf("Position: %s\n", get_nth_db_element(i)->matches[j]->position);
			printf("Round: %s\n", get_nth_db_element(i)->matches[j]->round);
			printf("Notes: %s\n", get_nth_db_element(i)->matches[j]->notes);
		}
	}

	return 0;
}
