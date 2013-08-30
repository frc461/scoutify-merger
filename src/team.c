#include <stdlib.h>
#include <string.h>

#include <src/team.h>

/*
 * Simply creates, allocates, and returns an empty team structure (pointers inside may not be initialized!)
 */
team_t *team_new()
{ team_t *ret = (team_t *)malloc(sizeof(team_t));
	return ret;
}
/*
 * Creates a new team struct and populates it with the arguments given as the data
 */
team_t *team_new_from_data(unsigned int number, char name[128], match_t **matches)
{ team_t *ret = team_new();

	/*
	 * TODO: add validations, perhaps detect if stuff isn't allocated and call functions to allocate it [matches ptr]
	 */
	
	ret->number = number;
	strcpy(ret->name, name);
	ret->matches = matches;

	return ret;
}

int team_free();
