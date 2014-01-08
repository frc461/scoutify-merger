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

#ifndef MATCH_H
#define MATCH_H

#include <src/fields.h>

typedef struct match {
	/* team is implied because the match should be withing a team struct */
	position_t position;

	char round[16];

	// note: for now we are disregarding event, we may add that functionality in the future,
	// but it can't hurt to have it in the form.
	
	int auto_shots;
	int auto_scores;
	int auto_goal;
	int teleop_shots;
	int teleop_scores;
	int teleop_goal;
	int climb_tier;

	char notes[256];
} match_t;

match_t *match_new();
match_t *match_new_from_data(position_t position,
                             char round[16],
                             int auto_shots,
                             int auto_scores,
                             int auto_goal,
                             int teleop_shots,
                             int teleop_scores,
                             int teleop_goal,
                             int climb_tier,
                             char notes[256]);
int match_set_from_data(match_t *in,
                        position_t position,
                        char round[16],
                        int auto_shots,
                        int auto_scores,
                        int auto_goal,
                        int teleop_shots,
                        int teleop_scores,
                        int teleop_goal,
                        int climb_tier,
                        char notes[256]);
int match_free();

int print_match(match_t *match);

#endif
