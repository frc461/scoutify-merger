/*
    Copyright Christopher Cooper and Kristofer Rye 2013

    This file is part of scoutify-hub.

    scoutify-hub is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    scoutify-hub is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with scoutify-hub.  If not, see <http://www.gnu.org/licenses/>.
*/

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
