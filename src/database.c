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

#include <stdlib.h>

#include <src/database.h>

/* UNDER NO CIRUMSTANCE SHOULD YOU DIRECTLY ACCESS THE DATABASE.
 *
 * ALWAYS USE THESE ABSTRACTION FUNCTIONS.
 */

int _db_end_ = 0;

/* The following are okay for use. */
void database_init() {
 	_db_ = malloc(sizeof(team_t *)*256);
	_db_end_ = 0;
}

int database_add_team(team_t *team) {
	if(_db_end_ >= 256)
		return -1;
	
	_db_[_db_end_] = team;
	_db_end_++;
	
	return 0;
}

team_t *database_get_nth_element(int n) {
	return n >= _db_end_ ? NULL :  _db_[n];
}

int database_set_nth_element(int n, team_t *team) {
	if(n >= _db_end_)
		return -1;
	
	_db_[n] = team;
	return 0;
}

/*  Delete an element out of the db by replacing it with the element at the end
 * and decrementing the end pointer.
 */
int database_delete_nth_element(int n) {
	if(n >= _db_end_)
		return -1;
	
	_db_[n]= _db_[_db_end_ - 1];
	_db_end_--;
}

/* Avoid the following two functions if at all possible. */
int _database_num_elements_() {
	return _db_end_;
}

team_t **_unrestricted_db_() {
	return _db_;
}
