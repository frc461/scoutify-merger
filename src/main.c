#include <src/main.h>

int main(int argc, char *argv[])
{
	match_t *match;
	init_db();
	if(argc < 2) return 0;

	match = load_match_file(argv[1], NULL);

	printf("Round: %s\n", match->round);

	return 0;
}
