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

#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>

#include <jansson.h>

#include <lib/tinydir.h>

#include <src/team.h>
#include <src/merge.h>

match_t *load_match_file(char *path, char *team);

team_t *load_team_dir(char *dir_path, char* team);

int load_dot_scoutify(char *dsf_path);

int dump_database_to_file(char *opath);

#endif
