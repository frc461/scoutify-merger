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

void database_init();

int database_add_team(team_t *team);

team_t *database_get_nth_element(int n);

int database_set_nth_element(int n, team_t *team);

int database_delete_nth_element(int n);

int _database_num_elements_();

team_t **_unrestricted_db_();

#endif
