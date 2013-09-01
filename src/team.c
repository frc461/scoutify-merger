#include <stdlib.h>
#include <string.h>

#include <src/team.h>

/*
 * Simply creates, allocates, and returns an empty team structure (pointers inside may not be initialized!)
 */
team_t *team_new()
{ team_t *ret = malloc(sizeof(team_t));
	return ret;
}
/*
 * Creates a new team struct and populates it with the arguments given as the data
 */
team_t *team_new_from_data(unsigned int number, char name[128], match_t **matches, unsigned int num_matches)
{ team_t *ret = team_new();

	/*
	 * TODO: add validations, perhaps detect if stuff isn't allocated and call functions to allocate it [matches ptr]
	 */
	
	ret->number = number;
	strcpy(ret->name, name);
	ret->matches = matches;
	ret->num_matches = num_matches;

	return ret;
}

int team_set_from_data(team_t *in, unsigned int number, char name[128], match_t **matches, unsigned int num_matches)
{
	in->number = number;
	strcpy(in->name, name);
	in->matches = matches;
	in->num_matches = num_matches;

	return 0;
}

int team_free();
