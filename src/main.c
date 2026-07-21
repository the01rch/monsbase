#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

int field_check(const char *field, cJSON *mon)
{
	if (strcmp(field, "name") == 0)
		return (printf("%s\n", cJSON_GetObjectItem(mon, field)->valuestring), 0);
	if (strcmp(field, "id") == 0 || strcmp(field, "bst") == 0) {
		printf("%lf\n", cJSON_GetObjectItem(mon, field)->valuedouble);
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
	printf("wrong field\n");
	return (1);
}

int main(int ac, const char **av) {
    /* Read whole file */
    FILE *f;
	long len;
	char *data;

	(void)ac;
	if (!av[1])
		return (1);
	f = fopen("data/mons_OU.json", "r");
	if (!f)
		return (1);

    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);
    data = malloc(len + 1);
	if (!data)
		return (fclose(f), 1);
    fread(data, 1, len, f);
    fclose(f);
    data[len] = '\0';

    /* Parse JSON */
    cJSON *root = cJSON_Parse(data);
	free(data);
	if (!root)
		return (1);
    cJSON *arr = cJSON_GetObjectItem(root, "pokemon");

    /* Print infos */
    for (int i = 0; i < cJSON_GetArraySize(arr); i++) {
        cJSON *mon = cJSON_GetArrayItem(arr, i);
		if (field_check(av[1], mon) == 1)
			return (1);
    }
    cJSON_Delete(root);
    return (0);
}
