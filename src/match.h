#ifndef MATCH_H
#define MATCH_H

typedef struct match {
	// team is implied because the match should be withing a team struct
	char position[2];
	char round[16];
	char notes[256];
} match_t;

match_t *match_new();
match_t *match_new_from_data(char position[2], char round[16], char notes[256]);
int match_set_from_data(match_t *in, char position[2], char round[16], char notes[256]);

int match_free();

#endif
