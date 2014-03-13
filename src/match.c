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
match_t *match_new()
{
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
                             char notes[65536])
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
                        char notes[65536])
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

	return 0;
}

int match_get_team_score(match_t *match)
{
	int score = 0;

	/* Autonomous calculations */
	if(match->auto_shot != AUTO_SHOT_FAIL) { /* If some shot was made during autonomous (we assume that there's only one) */
		/* 5 points for autonomous */
		score += 5;

		/* If we shot into the hot goal */
		if(match->auto_hot) {
			/* Another 5 points :D */
			score += 5;
		}

		if(match->auto_shot == AUTO_SHOT_HIGH_1) { /* If 1 high, add 10 */
			score += 10;
		} else if(match->auto_shot == AUTO_SHOT_LOW_1) { /* If 1 low, add 1 */
			score += 1;
		} else if(match->auto_shot == AUTO_SHOT_HIGH_2) { /* If 2 high, add 20 */
			score += 20;
		} else if(match->auto_shot == AUTO_SHOT_LOW_2) { /* If 2 low, add 2 */
			score += 2;
		}
	}

	/* 5 Points for auto mobility */
	if(match->auto_mobility)
		score += 5;

	/* 10 Points for each truss scored */
	score += match->trusses_scored * 10;

	/* 10 Points for each catch */
	score += match->catches_scored * 10;

	/* 5 Points for each pass or recieve */
	score += match->receives_scored * 5;
	score += match->passes_scored * 5;

	/* Generic goals */
	score += match->high_goals_scored * 10;
	score += match->low_goals_scored * 1;

	return score;
}

int match_get_team_value(match_t *match)
{
	int score = 0;

	int auton = 0;

	/* Autonomous calculations */
	if(match->auto_shot != AUTO_SHOT_FAIL) { /* If some shot was made during autonomous (we assume that there's only one) */
		/* 5 points for autonomous */
		auton += 5;

		/* If we shot into the hot goal */
		if(match->auto_hot) {
			/* Another 5 points :D */
			auton += 5;
		}

		if(match->auto_shot == AUTO_SHOT_HIGH_1) { /* If 1 high, add 10 */
			score += 10;
		} else if(match->auto_shot == AUTO_SHOT_LOW_1) { /* If 1 low, add 1 */
			score += 1;
		} else if(match->auto_shot == AUTO_SHOT_HIGH_2) { /* If 2 high, add 20 */
			score += 20;
		} else if(match->auto_shot == AUTO_SHOT_LOW_2) { /* If 2 low, add 2 */
			score += 2;
		}
	}

	/* 5 Points for auto mobility */
	if(match->auto_mobility)
		auton += 5;

	/* Weight auton and add to score */
	score += auton * AUTON_WEIGHT;

	/* 10 Points for each truss scored */
	score += match->trusses_scored * 10 * TRUSS_WEIGHT;

	/* 10 Points for each catch */
	score += match->catches_scored * 10 * CATCH_WEIGHT;

	/* 5 Points for each pass or recieve */
	score += match->receives_scored * 5 * ASSIST_WEIGHT;
	score += match->passes_scored * 5 * ASSIST_WEIGHT;

	/* Generic goals */
	score += match->high_goals_scored * 10 * HIGH_WEIGHT;
	score += match->low_goals_scored * 1 * LOW_WEIGHT;

	return score;
}
