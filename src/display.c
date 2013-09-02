#include <stdio.h>

#include <src/database.h>
#include <src/team.h>

#include <src/display.h>

void database_display()
{
	for(int i = 0; database_get_nth_element(i); i += 1) {
		team_t *curteam = database_get_nth_element(i);
		printf("%d: Team %8lu with sort-value %8d\n", i, curteam->number, curteam->value);
	}
}

void database_display_table_mode()
{
	printf("%6s | %16s | %12s\n", "", "TEAM NUMBER", "SORT VALUE");
	
	for(int i = 0; database_get_nth_element(i); i += 1) {
		team_t *curteam = database_get_nth_element(i);
		
		printf("%6d | %16u | %12d\n", i, curteam->number, curteam->value);
	}
}
