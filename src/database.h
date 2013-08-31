#ifndef DATABASE_H
#define DATABASE_H

#include <src/team.h>

/*
 * UNDER NO CIRUMSTANCE SHOULD YOU DIRECTLY ACCESS THE DATABASE.
 * 
 * ALWAYS USE THESE ABSTRACTION FUNCTIONS.
 */

team_t **db; // global database (array of teams)

extern int db_end2; // pointer to end of db

void init_db();

int add_to_db(team_t *team);

team_t *get_nth_db_element(int n);

int set_nth_db_element(int n, team_t *team);

#endif
