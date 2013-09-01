#include <stdlib.h>

#include <src/database.h>

/*
 * UNDER NO CIRUMSTANCE SHOULD YOU DIRECTLY ACCESS THE DATABASE.
 *
 * ALWAYS USE THESE ABSTRACTION FUNCTIONS.
 */

int _db_end_ = 0;

void init_db() {
 	_db_ = malloc(sizeof(team_t *)*256);
	_db_end_ = 0;
}

int add_to_db(team_t *team) {
	if(_db_end_ >= 256) return -1;
	_db_[_db_end_] = team;
	_db_end_++;
	return 0;
}

team_t *get_nth_db_element(int n) {
	if(n >= _db_end_) return NULL;
	else return _db_[n];
}

int set_nth_db_element(int n, team_t *team) {
	if(n >= _db_end_) return -1;
	_db_[n] = team;
	return 0;
}

/*
 * Delete an element out of the db by replacing it with the element at the end
 * and decrementing the end pointer.
 */
int delete_nth_db_element(int n) {
	if(n >= _db_end_) return -1;
	_db_[n]= _db_[_db_end_ - 1];
	_db_end_--;
}

/*
 * Avoid the following two functions if at all possible.
 */
int num_db_elements() {
	return _db_end_;
}

team_t **unrestricted_db() {
	return _db_;
}
