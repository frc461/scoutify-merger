#ifndef TEAM_H
#define TEAM_H

#include <src/match.h>

typedef struct team {
	unsigned int number;
	char name[128];
	int value;

	match_t **matches;
	unsigned int num_matches;
} team_t;

team_t *team_new();
team_t *team_new_from_data(unsigned int number, char name[128], match_t **matches, unsigned int num_matches);
int team_set_from_data(team_t *in, unsigned int number, char name[128], match_t **matches, unsigned int num_matches);

int team_free();

#endif
