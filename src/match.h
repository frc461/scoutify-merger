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

#ifndef MATCH_H
#define MATCH_H

#include <src/fields.h>

typedef struct match {
	// team is implied because the match should be withing a team struct
	int position;
	/*
	 * 1 = R1
	 * 2 = R2
	 * 3 = R3
	 * 4 = B1
	 * 5 = B2
	 * 6 = B3
	 */
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
match_t *match_new_from_data(int position,
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
                        int position,
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

#endif
