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

	db = load_dot_scoutify(argv[1]);

	for(int i = 0; db[i]; i++) {
		printf("TEAM: %u\n", db[i]->number);
		for(int j = 0; db[i]->matches[j]; j++) {
			printf("Position: %s\n", db[i]->matches[j]->position);
			printf("Round: %s\n", db[i]->matches[j]->round);
			printf("Notes: %s\n", db[i]->matches[j]->notes);
		}
	}

	return 0;
}
