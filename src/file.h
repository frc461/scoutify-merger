#ifndef FILE_H
#define FILE_H

#include <src/match.h>
#include <src/json.h>
#include <stdio.h>

match_t *load_match_file(char *path, char *team);

#endif
