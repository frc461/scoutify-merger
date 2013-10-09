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

int position_string_to_int(char *position)
{   int ret;
	if(!strcmp(position, "R1")) ret = 1;
	else if(!strcmp(position, "R2")) ret = 2;
	else if(!strcmp(position, "R3")) ret = 3;
	else if(!strcmp(position, "B1")) ret = 4;
	else if(!strcmp(position, "B2")) ret = 5;
	else if(!strcmp(position, "B3")) ret = 6;
	else {
		fprintf(stderr, "ERROR: Position string not recognized: %s\n", position);
		ret = 0;
	}

	return ret;
}

char *position_int_to_string(int position)
{   char *ret;

	switch(position) {
	case 1:
		ret = "R1";
		break;
	case 2:
		ret = "R2";
		break;
	case 3:
		ret = "R3";
		break;
	case 4:
		ret = "B1";
		break;
	case 5:
		ret = "B2";
		break;
	case 6:
		ret = "B3";
		break;
	default:
		fprintf(stderr, "ERROR: Position integer not recognized: %u\n", position);
		ret = "";
		break;
	}

	return ret;
}
