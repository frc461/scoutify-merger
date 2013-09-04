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

#include <src/json.h>
#include <src/file.h>

match_t *load_match_file(char *path, char *team)
{   match_t *ret = match_new();
	json_t *json;
	json_error_t error;

	json = json_load_file(path, 0, &error);
	if(!json) {
		fprintf(stderr, "ERROR: %s\n", error.text);
		return NULL;
	}
	
	if(team && strcmp(team, json_string_value(json_object_get(json, "team")))) {
		fprintf(stderr, "ERROR: Teams do not match. (\"%s\" and \"%s\")\n",
		        team,
		        json_string_value(json_object_get(json, "team")));
		return NULL;
	}

	match_set_from_data(ret,
	                    (char *)json_string_value(json_object_get(json, "position")),
	                    (char *)json_string_value(json_object_get(json, "round")),
	                    (char *)json_string_value(json_object_get(json, "notes")));

	return ret;
}

team_t *load_team_dir(char *dir_path, char *team)
{   team_t *ret = team_new();
	match_t **matches = malloc(sizeof(match_t *)*128);
	int i = 0;
	tinydir_dir dir;
	tinydir_open(&dir, dir_path);

	while(dir.has_next) {
		tinydir_file file;
		match_t *match;
		tinydir_readfile(&dir, &file);

		if(!file.is_dir) { // not a directory (assuming therefore regular file)

			char *dot = strrchr(file.name, '.');
			if(dot && !strcmp(dot, ".json")) { // ends w/ .json

				char *fullpath = malloc((strlen(dir_path) +
				                         strlen(team) +
				                         strlen(file.name))
				                        * sizeof(char));
				strcpy(fullpath, dir_path);
				strcat(fullpath, "/");
				strcat(fullpath, file.name);

				if(match = load_match_file(fullpath, team)) { // make sure there were no errors
					matches[i] = match; // add to matches
					i++;
				}
			}
		}

		tinydir_next(&dir);
	}

	tinydir_close(&dir);

	if(i == 0) return NULL;
	else return team_new_from_data((unsigned int)atoi(team), "", matches, i);
}

int load_dot_scoutify(char *dsf_path)
{
	int i = 0;
	tinydir_dir dir;
	tinydir_open(&dir, dsf_path);

	while(dir.has_next) {
		tinydir_file file;
		team_t *team;
		tinydir_readfile(&dir, &file);

		if(file.is_dir && // a directory, assuming to be a team dir
		   (strcmp(".", file.name) && strcmp("..", file.name))) { // is not . or ..

			char *fullpath = malloc((strlen(dsf_path) +
			                         strlen(file.name))
			                        * sizeof(char));

			strcpy(fullpath, dsf_path);
			strcat(fullpath, "/");
			strcat(fullpath, file.name);
			
			if(team = load_team_dir(fullpath, file.name)) { // make sure there were matches
				database_add_team(team); // add to db
				i++;
			}
		}

		tinydir_next(&dir);
	}

	tinydir_close(&dir);

	if(i == 0) return 1;
	else return 0;
}

int write_db_to_file(char *path)
{
	json_dump_file(make_json_from_db(), path, 0);
	return 0;
}

int populate_db_from_file(char *path)
{
	json_t *json;
	json_error_t error;

	json = json_load_file(path, 0, &error);
	if(!json) {
		fprintf(stderr, "ERROR: %s\n", error.text);
		return -1;
	}

	populate_db_from_json(json);

	return 0;

}
