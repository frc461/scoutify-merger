#include <stdio.h>

#include <src/database.h>
#include <src/team.h>

#include <src/display.h>

void database_display()
{
	team_t **db = unrestricted_db();
	
	for(int i = 0; i < num_db_elements(); i += 1) {
		team_t *curteam = db[i];
		printf("Team %8lu [%s]\n", curteam->number, curteam->name);
	}
}
