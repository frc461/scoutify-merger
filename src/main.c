#include <stdio.h>

#include <src/main.h>
#include <jansson.h>

int main(int argc, char *argv[])
{
	init_db();
	if(argc < 2) return 0;
	json_t *json;
	json_error_t error;

	json = json_load_file(argv[1], 0, &error);
	if(!json) {
		printf("error\n");
	}
	else {
		printf(json_string_value(json_object_get(json, "team")));
		printf("\n");
	}
	return 0;
}
