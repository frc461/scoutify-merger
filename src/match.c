/*
  Copyright Christopher Cooper and Kristofer Rye 2013

  This file is part of scoutify-merger.

  scoutify-merger is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  scoutify-merger is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with scoutify-merger.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <src/match.h>

/* Simply creates, allocates, and returns an empty match structure (pointers inside may not be initialized!) */
match_t *match_new(){
match_t *ret = malloc(sizeof(match_t));
	return ret;
}

/* Creates a new match struct and populates it with the arguments given as the data */
match_t *match_new_from_data(position_t position,
                             char round[16],
                             auto_shot_t auto_shot,
                             bool auto_hot,
                             bool auto_mobility,
                             int high_goals_scored,
                             int high_goals_attempted,
                             int low_goals_scored,
                             int low_goals_attempted,
                             int trusses_scored,
                             int trusses_attempted,
                             int catches_scored,
                             int catches_attempted,
                             int passes_scored,
                             int passes_attempted,
                             int receives_scored,
                             int receives_attempted,
                             int blocks_scored,
                             int blocks_attempted,
                             char notes[4096])
{ match_t *ret = match_new();

	/* TODO: add validations, perhaps detect if stuff isn't allocated and call functions to allocate it [matches ptr] */
	
	ret->position = position;
	strcpy(ret->round, round);
	ret->auto_shot = auto_shot;
	ret->auto_hot = auto_hot;
	ret->auto_mobility = auto_mobility;
	ret->high_goals_scored = high_goals_scored;
	ret->high_goals_attempted = high_goals_attempted;
	ret->low_goals_scored = low_goals_scored;
	ret->low_goals_attempted = low_goals_attempted;
	ret->trusses_scored = trusses_scored;
	ret->trusses_attempted = trusses_attempted;
	ret->catches_scored = catches_scored;
	ret->catches_attempted = catches_attempted;
	ret->passes_scored = passes_scored;
	ret->passes_attempted = passes_attempted;
	ret->receives_scored = receives_scored;
	ret->receives_attempted = receives_attempted;
	ret->blocks_scored = blocks_scored;
	ret->blocks_attempted = blocks_attempted;
	strcpy(ret->notes, notes);

	return ret;
}

int match_set_from_data(match_t *in,
                        position_t position,
                        char round[16],
                        auto_shot_t auto_shot,
                        bool auto_hot,
                        bool auto_mobility,
                        int high_goals_scored,
                        int high_goals_attempted,
                        int low_goals_scored,
                        int low_goals_attempted,
                        int trusses_scored,
                        int trusses_attempted,
                        int catches_scored,
                        int catches_attempted,
                        int passes_scored,
                        int passes_attempted,
                        int receives_scored,
                        int receives_attempted,
                        int blocks_scored,
                        int blocks_attempted,
                        char notes[4096])
{
	in->position = position;
	strcpy(in->round, round);
	in->auto_shot = auto_shot;
	in->auto_hot = auto_hot;
	in->auto_mobility = auto_mobility;
	in->high_goals_scored = high_goals_scored;
	in->high_goals_attempted = high_goals_attempted;
	in->low_goals_scored = low_goals_scored;
	in->low_goals_attempted = low_goals_attempted;
	in->trusses_scored = trusses_scored;
	in->trusses_attempted = trusses_attempted;
	in->catches_scored = catches_scored;
	in->catches_attempted = catches_attempted;
	in->passes_scored = passes_scored;
	in->passes_attempted = passes_attempted;
	in->receives_scored = receives_scored;
	in->receives_attempted = receives_attempted;
	in->blocks_scored = blocks_scored;
	in->blocks_attempted = blocks_attempted;
	strcpy(in->notes, notes);

	return 0;
}

int match_free();

int print_match(match_t *match)
{
	printf("position_num: %s\n", position_to_string(match->position));
	printf("round: %s\n", match->round);
	printf("auto_shot: %s\n", auto_shot_to_string(match->auto_shot));
	printf("auto_hot: %s\n", match->auto_hot ? "yes" : "no");
	printf("auto_mobility: %s\n", match->auto_mobility ? "yes" : "no");
	printf("high_goals_scored: %u\n", match->high_goals_scored);
	printf("high_goals_attempted: %u\n", match->high_goals_attempted);
	printf("low_goals_scored: %u\n", match->low_goals_scored);
	printf("low_goals_attempted: %u\n", match->low_goals_attempted);
	printf("trusses_scored: %u\n", match->trusses_scored);
	printf("trusses_attempted: %u\n", match->trusses_attempted);
	printf("catches_scored: %u\n", match->catches_scored);
	printf("catches_attempted: %u\n", match->catches_attempted);
	printf("passes_scored: %u\n", match->passes_scored);
	printf("passes_attempted: %u\n", match->passes_attempted);
	printf("receives_scored: %u\n", match->receives_scored);
	printf("receives_attempted: %u\n", match->receives_attempted);
	printf("blocks_scored: %u\n", match->blocks_scored);
	printf("blocks_attempted: %u\n", match->blocks_attempted);
	printf("notes: %s\n", match->notes);

}
