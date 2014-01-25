/*
    Copyright Christopher Cooper and Kristofer Rye 2013

    This file is part of scoutify-merger.

    scoutify-merger is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    scoutify-merger is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with scoutify-merger.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <src/database.h>
#include <src/json.h>

bool json_boolean_value(json_t *object)
{	bool ret;

	if json_is_true(object) ret = true;
	else if json_is_false(object) ret = false;
	else {
		fprintf(stderr, "ERROR: json value %s is not a boolean", json_dumps(object, 0));
		ret = false;
	}

	return ret;
}

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

			json_object_set(match, "position_num", json_integer(database_get_nth_element(i)->matches[j]->position));
			json_object_set(match, "round", json_string(database_get_nth_element(i)->matches[j]->round));
			json_object_set(match, "auto_shot", json_integer(database_get_nth_element(i)->matches[j]->auto_shot));
			json_object_set(match, "auto_hot", json_boolean(database_get_nth_element(i)->matches[j]->auto_hot));
			json_object_set(match, "auto_mobility", json_boolean(database_get_nth_element(i)->matches[j]->auto_mobility));
			json_object_set(match, "high_goals_scored", json_integer(database_get_nth_element(i)->matches[j]->high_goals_scored));
			json_object_set(match, "high_goals_attempted", json_integer(database_get_nth_element(i)->matches[j]->high_goals_attempted));
			json_object_set(match, "low_goals_scored", json_integer(database_get_nth_element(i)->matches[j]->low_goals_scored));
			json_object_set(match, "low_goals_attempted", json_integer(database_get_nth_element(i)->matches[j]->low_goals_attempted));
			json_object_set(match, "trusses_scored", json_integer(database_get_nth_element(i)->matches[j]->trusses_scored));
			json_object_set(match, "trusses_attempted", json_integer(database_get_nth_element(i)->matches[j]->trusses_attempted));
			json_object_set(match, "catches_scored", json_integer(database_get_nth_element(i)->matches[j]->catches_scored));
			json_object_set(match, "catches_attempted", json_integer(database_get_nth_element(i)->matches[j]->catches_attempted));
			json_object_set(match, "passes_scored", json_integer(database_get_nth_element(i)->matches[j]->passes_scored));
			json_object_set(match, "passes_attempted", json_integer(database_get_nth_element(i)->matches[j]->passes_attempted));
			json_object_set(match, "receives_scored", json_integer(database_get_nth_element(i)->matches[j]->receives_scored));
			json_object_set(match, "receives_attempted", json_integer(database_get_nth_element(i)->matches[j]->receives_attempted));
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

			matches[j] = match_new_from_data(json_integer_value(json_object_get(match, "position_num")),
			                                 (char *)json_string_value(json_object_get(match, "round")),
			                                 json_integer_value(json_object_get(match, "auto_shot")),
			                                 json_boolean_value(json_object_get(match, "auto_hot")),
			                                 json_boolean_value(json_object_get(match, "auto_mobility")),
			                                 json_integer_value(json_object_get(match, "high_goals_scored")),
			                                 json_integer_value(json_object_get(match, "high_goals_attempted")),
			                                 json_integer_value(json_object_get(match, "low_goals_scored")),
			                                 json_integer_value(json_object_get(match, "low_goals_attempted")),
			                                 json_integer_value(json_object_get(match, "trusses_scored")),
			                                 json_integer_value(json_object_get(match, "trusses_attempted")),
			                                 json_integer_value(json_object_get(match, "catches_scored")),
			                                 json_integer_value(json_object_get(match, "catches_attempted")),
			                                 json_integer_value(json_object_get(match, "passes_scored")),
			                                 json_integer_value(json_object_get(match, "passes_attempted")),
			                                 json_integer_value(json_object_get(match, "receives_scored")),
			                                 json_integer_value(json_object_get(match, "receives_attempted")),
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
