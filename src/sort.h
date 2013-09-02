#ifndef SORT_H
#define SORT_H

#include <src/database.h>

int find_value(team_t *team);

int set_sort_value(team_t *team);

int value(const team_t *team);

int compare(const void *a, const void *b);

int database_sort();

#endif
