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
		fprintf(stderr, "ERROR: Teams do not match. (\"%s\" and \"%s\")\n", team, json_string_value(json_object_get(json, "team")));
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
		char *fullpath = malloc((strlen(dir_path)+strlen(team)+1)*sizeof(char));
		match_t *match;
		tinydir_readfile(&dir, &file);

		if(!file.is_dir) { // not a directory (assuming therefore regular file)

			char *dot = strrchr(file.name, '.');
			if(dot && !strcmp(dot, ".json")) { // ends w/ .json

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
{   int i = 0;
	tinydir_dir dir;
	tinydir_open(&dir, dsf_path);

	while(dir.has_next) {
		tinydir_file file;
		char *fullpath = malloc((strlen(dsf_path)+8)*sizeof(char));
		team_t *team;
		tinydir_readfile(&dir, &file);

		if(file.is_dir && // a directory, assuming to be a team dir
		   (strcmp(".", file.name) && strcmp("..", file.name))) { // is not . or ..
			
			strcpy(fullpath, dsf_path);
			strcat(fullpath, "/");
			strcat(fullpath, file.name);
			
			if(team = load_team_dir(fullpath, file.name)) { // make sure there were matches
				add_to_db(team); // add to db
				i++;
			}
		}

		tinydir_next(&dir);
	}

	tinydir_close(&dir);

	if(i == 0) return 1;
	else return 0;
}
