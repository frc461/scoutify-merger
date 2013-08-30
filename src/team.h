#ifndef TEAM_H
#define TEAM_H

#include <src/match.h>

typedef struct team {
	unsigned int number;
	char name[128];

	match_t **matches;
} team_t;

team_t *team_new();
team_t *team_new_from_data(unsigned int number, char name[128], match_t **matches);

int team_free();

#endif
