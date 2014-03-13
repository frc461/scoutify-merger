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

#include <src/database.h>
#include <src/team.h>

#include <src/display.h>

void database_display()
{
	team_t *curteam;

	for(int i = 0; curteam = database_get_nth_element(i); i += 1) {
		printf("%d: Team %8u with sort-value %8f\n", i, curteam->number, curteam->value);
	}
}

void database_display_table_mode()
{
	printf("%-6s | %-16s | %12s | %-32s\n", "", "TEAM NUMBER", "SORT VALUE", "TEAM NAME");

	team_t *curteam;

	for(int i = 0; curteam = database_get_nth_element(i); i += 1) {
		printf("%-6d | %-16u | %12f | %-32s\n", i, curteam->number, curteam->value, curteam->name);
	}
}
