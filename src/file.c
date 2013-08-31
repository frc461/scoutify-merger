#include <src/file.h>

match_t *load_match_file(char *path, char *team)
{   match_t *ret = match_new();
	json_t *json;
	json_error_t error;

	json = json_load_file(path, 0, &error);
	if(!json) {
		perror("ERROR: %s\n", error.text);
		return NULL;
	}
	
	if(team && strcmp(team, json_string_value(json_object_get(json, "team")))) {
		perror("ERROR: Teams do not match. (\"%s\" and \"%s\")\n", team, json_string_value(json_object_get(json, "team")));
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
	match_t **matches = malloc(sizeof(match_t)*20);
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
					matches[0] = match; // add to matches
					i++;
				}
			}
		}

		tinydir_next(&dir);
	}

	tinydir_close(&dir);
	
	return team_new_from_data((unsigned int)atoi(team), "", matches);
}

team_t **load_dot_scoutify(char *dsf_path)
{   team_t **ret;
}
