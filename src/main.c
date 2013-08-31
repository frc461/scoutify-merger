#include <src/main.h>

int main(int argc, char *argv[])
{
	team_t *team;
	init_db();
	if(argc < 2) return 0;

	team = load_team_dir(argv[1], &strrchr(argv[1], '/')[1]);

	printf("Position: %s\n", team->matches[0]->position);
	printf("Round: %s\n", team->matches[0]->round);
	printf("Notes: %s\n", team->matches[0]->notes);

	return 0;
}
