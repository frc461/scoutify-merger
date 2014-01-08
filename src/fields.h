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

#ifndef FIELDS_H
#define FIELDS_H

#include <stdbool.h>

typedef enum {
	POSITION_R1,
	POSITION_R2,
	POSITION_R3,
	POSITION_B1,
	POSITION_B2,
	POSITION_B3
} position_t;

typedef enum {
	AUTO_SHOT_FAIL,
	AUTO_SHOT_HIGH,
	AUTO_SHOT_LOW
} auto_shot_t;

position_t string_to_position(char *position);

char *position_to_string(int position);

auto_shot_t string_to_auto_shot(char *auto_shot);

char *auto_shot_to_string(int auto_shot);

bool yes_no_string_to_boolean(char *yes_no);

#endif
