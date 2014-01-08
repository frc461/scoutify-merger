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

#include <string.h>
#include <stdio.h>

#include <src/fields.h>

position_t string_to_position(char *position)
{	position_t ret;

	if(!strcmp(position, "R1")) ret = POSITION_R1;
	else if(!strcmp(position, "R2")) ret = POSITION_R2;
	else if(!strcmp(position, "R3")) ret = POSITION_R3;
	else if(!strcmp(position, "B1")) ret = POSITION_B1;
	else if(!strcmp(position, "B2")) ret = POSITION_B2;
	else if(!strcmp(position, "B3")) ret = POSITION_B3;
	else {
		fprintf(stderr, "ERROR: Position string not recognized: %s\n", position);
		ret = 0;
	}

	return ret;
}

char *position_to_string(int position)
{	char *ret;

	switch(position) {
	case POSITION_R1:
		ret = "R1";
		break;
	case POSITION_R2:
		ret = "R2";
		break;
	case POSITION_R3:
		ret = "R3";
		break;
	case POSITION_B1:
		ret = "B1";
		break;
	case POSITION_B2:
		ret = "B2";
		break;
	case POSITION_B3:
		ret = "B3";
		break;
	default:
		fprintf(stderr, "ERROR: Position integer not recognized: %u\n", position);
		ret = "";
		break;
	}

	return ret;
}
