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

#ifndef DATABASE_H
#define DATABASE_H

#include <src/team.h>

/*
 * UNDER NO CIRUMSTANCE SHOULD YOU DIRECTLY ACCESS THE DATABASE.
 * 
 * ALWAYS USE THESE ABSTRACTION FUNCTIONS.
 */

team_t **_db_; // global database (array of teams)

extern int _db_end_; // pointer to end of db

/*
 * The following are okay for use.
 */

void database_init();

int database_add_team(team_t *team);

team_t *database_get_nth_element(int n);

int database_set_nth_element(int n, team_t *team);

int database_delete_nth_element(int n);

/*
 * Avoid the following two functions if at all possible.
 */

int _database_num_elements_();

team_t **_unrestricted_db_();

#endif
