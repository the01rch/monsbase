#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

// get the file and return it into a char *data
char *get_data(const char *path)
{
	FILE *f;
	long len;
	char *data;

	f = fopen(path, "r");
	if (!f)
		return (NULL);

	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);
	data = malloc(len + 1);
	if (!data)
		return (fclose(f), NULL);
	fread(data, 1, len, f);
	fclose(f);
	data[len] = '\0';
	return (data);
}

// check the field of the mon to return its content
int field_check(const char *field, cJSON *mon)
{
	if (strcmp(field, "id") == 0 || strcmp(field, "bst") == 0) {
		printf("%d\n", cJSON_GetObjectItem(mon, field)->valueint);
		return (0);
	}
	if (strcmp(field, "types") == 0 || strcmp(field, "abilities") == 0)	{
		cJSON *arr = cJSON_GetObjectItem(mon, field);
		for (int i = 0; i < cJSON_GetArraySize(arr); i++) {
			cJSON *tmp = cJSON_GetArrayItem(arr, i);
			printf("%s\n", tmp->valuestring);
		}
		return (0);
	}
	if (strncmp(field, "base_stats.", 11) == 0) {
		cJSON *new = cJSON_GetObjectItem(mon, "base_stats");
		for (int i = 0; i < cJSON_GetArraySize(new); i++) {
			cJSON *tmp = cJSON_GetArrayItem(new, i);
			cJSON *cnt;
			cnt = oh;
			if (strncmp(field, "base_stats.hp", 13) == 0) {
				printf("coucou\n");
				if (strcmp(tmp, "hp") == 0)
				//printf("%d\n", cJSON_GetObjectItem(tmp, field)->valueint);
				return (0);
			}
		}
	}
	return (1);
}

int main(int ac, const char **av) {

	char *data;
	(void)ac;
	if (!av[1] || !av[2])
		return (1);
	data = get_data("data/mons_OU.json");
	if (!data)
		return (1);
    cJSON *root = cJSON_Parse(data);
	free(data);
	if (!root)
		return (1);
    cJSON *arr = cJSON_GetObjectItem(root, "pokemon");
    for (int i = 0; i < cJSON_GetArraySize(arr); i++) {
        cJSON *mon = cJSON_GetArrayItem(arr, i);
        cJSON *name = cJSON_GetObjectItem(mon, "name");
		if (strcmp(name->valuestring, av[1]) == 0) {
			printf("%s:\n", name->valuestring);
			if (field_check(av[2], mon) == 1)
				printf("wrong field\n");
			break ;
		}
    }
    cJSON_Delete(root);
    return (0);
}
