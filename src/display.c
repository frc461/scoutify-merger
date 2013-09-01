#include <stdio.h>

#include <src/database.h>
#include <src/team.h>

#include <src/display.h>

void database_display()
{
	team_t **db = _unrestricted_db_();
	
	for(int i = 0; i < _database_num_elements_(); i += 1) {
		team_t *curteam = database_get_nth_element(i);
		printf("Team %8lu [%s]\n", curteam->number, curteam->name);
	}
}
