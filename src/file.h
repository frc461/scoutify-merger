#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>

#include <lib/tinydir.h>

#include <src/team.h>
#include <src/json.h>
#include <src/database.h>

match_t *load_match_file(char *path, char *team);

team_t *load_team_dir(char *dir_path, char* team);

int load_dot_scoutify(char *dsf_path);

#endif
