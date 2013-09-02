#include <stdlib.h>

#include <src/database.h>

/*
 * UNDER NO CIRUMSTANCE SHOULD YOU DIRECTLY ACCESS THE DATABASE.
 *
 * ALWAYS USE THESE ABSTRACTION FUNCTIONS.
 */

int _db_end_ = 0;

void database_init() {
 	_db_ = malloc(sizeof(team_t *)*256);
	_db_end_ = 0;
}

int database_add_team(team_t *team) {
	if(_db_end_ >= 256) return -1;
	_db_[_db_end_] = team;
	_db_end_++;
	return 0;
}

/*
 * The following are okay for use.
 */

team_t *database_get_nth_element(int n) {
	if(n >= _db_end_) return NULL;
	else return _db_[n];
}

int database_set_nth_element(int n, team_t *team) {
	if(n >= _db_end_) return -1;
	_db_[n] = team;
	return 0;
}

/*
 * Delete an element out of the db by replacing it with the element at the end
 * and decrementing the end pointer.
 */
int database_delete_nth_element(int n) {
	if(n >= _db_end_) return -1;
	_db_[n]= _db_[_db_end_ - 1];
	_db_end_--;
}

/*
 * Avoid the following two functions if at all possible.
 */

int _database_num_elements_() {
	return _db_end_;
}

team_t **_unrestricted_db_() {
	return _db_;
}
