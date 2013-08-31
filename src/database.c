#include <stdlib.h>

#include <src/database.h>

// UNDER NO CIRUMSTANCE SHOULD YOU DIRECTLY ACCESS THE DATABASE.
// ALWAYS USE THESE ABSTRACTION FUNCTIONS.

void init_db() { 
 	db = malloc(sizeof(team_t)*256);
	db_end2 = 0;
}

int add_to_db(team_t *team) {
	if(db_end2 >= 256) return -1;
	db[db_end2] = team;
	db_end2++;
	return 0;
}

team_t *get_nth_db_element(int n) {
	if(n >= db_end2) return NULL;
	else return db[n];
}

int set_nth_db_element(int n, team_t *team) {
	if(n >= db_end2) return -1;
	db[n] = team;
	return 0;
}
