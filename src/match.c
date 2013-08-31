#include <stdlib.h>
#include <string.h>

#include <src/match.h>

/*
 * Simply creates, allocates, and returns an empty match structure (pointers inside may not be initialized!)
 */
match_t *match_new()
{ match_t *ret = malloc(sizeof(match_t));
	return ret;
}
/*
 * Creates a new match struct and populates it with the arguments given as the data
 */
match_t *match_new_from_data(char position[2], char round[16], char notes[256])
{ match_t *ret = match_new();

	/*
	 * TODO: add validations, perhaps detect if stuff isn't allocated and call functions to allocate it [matches ptr]
	 */
	
	strcpy(ret->position, position);
	strcpy(ret->round, round);
	strcpy(ret->notes, notes);

	return ret;
}

int match_set_from_data(match_t *in, char position[2], char round[16], char notes[256])
{
	strcpy(in->position, position);
	strcpy(in->round, round);
	strcpy(in->notes, notes);

	return 0;
}

int match_free();
