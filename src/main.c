#include "pokemon.h"

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

bool json_parser(const char *path, const char *object)
{
	char *data;

	data = get_data(path);
	if (!data)
		return (false);
    cJSON *root = cJSON_Parse(data);
	free(data);
	if (!root)
		return (false);
    cJSON *arr = cJSON_GetObjectItem(root, object);
    for (int i = 0; i < cJSON_GetArraySize(arr); i++) {
        cJSON *mon = cJSON_GetArrayItem(arr, i);
		fill2struct(object);
    }
    cJSON_Delete(root);
	return (true);
}

int main(int ac, const char **av) {
	(void)ac;

	if (!av[1] || !av[2])
		return (1);
    return (0);
}
