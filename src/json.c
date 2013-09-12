/*
    Copyright Christopher Cooper and Kristofer Rye 2013

    This file is part of scoutify-hub.

    scoutify-hub is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    scoutify-hub is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with scoutify-hub.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <src/database.h>
#include <src/json.h>

json_t *make_json_from_db()
{   json_t *ret;
	ret = json_array();

	for(int i = 0; database_get_nth_element(i); i++) {

		json_t *team;
		team = json_object();

		json_object_set(team, "number", json_integer(database_get_nth_element(i)->number));
		json_object_set(team, "name", json_string(database_get_nth_element(i)->name));
		json_object_set(team, "value", json_integer(database_get_nth_element(i)->value));

		json_t *matches;
		matches = json_array();

		for(int j = 0; j < database_get_nth_element(i)->num_matches; j++) {

			json_t *match;
			match = json_object();

			json_object_set(match, "position", json_integer(database_get_nth_element(i)->matches[j]->position));
			json_object_set(match, "round", json_string(database_get_nth_element(i)->matches[j]->round));
			json_object_set(match, "notes", json_string(database_get_nth_element(i)->matches[j]->notes));

			json_array_append(matches, match);
		}

		json_object_set(team, "matches", matches);

		json_array_append(ret, team);
	}

	return ret;
}

int populate_db_from_json(json_t *json)
{
	for(int i = 0; i < json_array_size(json); i++) {
		json_t *team = json_array_get(json, i);

		match_t **matches = malloc(sizeof(match_t *)*128);
		json_t *matches_json = json_object_get(team, "matches");

		int j;
		for(j = 0; j < json_array_size(matches_json); j++) {
			json_t *match = json_array_get(matches_json, j);
			
			matches[j] = match_new_from_data(json_integer_value(json_object_get(match, "position")),
			                                 (char *)json_string_value(json_object_get(match, "round")),
			                                 (char *)json_string_value(json_object_get(match, "notes")));
		}
		
		database_add_team(team_new_from_data_sorted(json_integer_value(json_object_get(team, "number")),
		                                            (char *)json_string_value(json_object_get(team, "name")),
		                                            matches,
		                                            (unsigned int)j,
		                                            json_integer_value(json_object_get(team, "value"))));
	}

	return 0;
}
