#include <src/main.h>

int main(int argc, char *argv[])
{
	team_t **teams;
	init_db();
	if(argc < 2) return 0;

	teams = load_dot_scoutify(argv[1]);

	for(int i = 0; teams[i]; i++) {
		printf("TEAM: %u\n", teams[i]->number);
		for(int j = 0; teams[i]->matches[j]; j++) {
			printf("Position: %s\n", teams[i]->matches[j]->position);
			printf("Round: %s\n", teams[i]->matches[j]->round);
			printf("Notes: %s\n", teams[i]->matches[j]->notes);
		}
	}

	return 0;
}
