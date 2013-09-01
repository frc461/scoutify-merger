#include <stdlib.h>

#include <src/database.h>

/*
 * UNDER NO CIRUMSTANCE SHOULD YOU DIRECTLY ACCESS THE DATABASE.
 *
 * ALWAYS USE THESE ABSTRACTION FUNCTIONS.
 */

int db_end = 0;

void init_db() {
 	db = malloc(sizeof(team_t *)*256);
	db_end = 0;
}

int add_to_db(team_t *team) {
	if(db_end >= 256) return -1;
	db[db_end] = team;
	db_end++;
	return 0;
}

team_t *get_nth_db_element(int n) {
	if(n >= db_end) return NULL;
	else return db[n];
}

int set_nth_db_element(int n, team_t *team) {
	if(n >= db_end) return -1;
	db[n] = team;
	return 0;
}

/*
 * Delete an element out of the db by replacing it with the element at the end
 * and decrementing the end pointer.
 */
int delete_nth_db_element(int n) {
	if(n >= db_end) return -1;
	db[n]= db[db_end - 1];
	db_end--;
}

/*
 * Avoid the following two functions if at all possible.
 */
int num_db_elements() {
	return db_end;
}

team_t **unrestricted_db() {
	return db;
}
