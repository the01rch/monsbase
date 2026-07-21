#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

int main() {
    /* Read whole file */
    FILE *f = fopen("data/mons_OU.json", "r");
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *data = malloc(len + 1);
    fread(data, 1, len, f);
    fclose(f);
    data[len] = '\0';

    /* Parse JSON */
    cJSON *root = cJSON_Parse(data);
    cJSON *arr = cJSON_GetObjectItem(
                    cJSON_GetObjectItem(
                        cJSON_GetObjectItem(root, "tiers"), "OU"),
                    "pokemon");

    /* Print names */
    for (int i = 0; i < cJSON_GetArraySize(arr); i++) {
        cJSON *mon = cJSON_GetArrayItem(arr, i);
        printf("%s\n", cJSON_GetObjectItem(mon, "name")->valuestring);
    }

    cJSON_Delete(root);
    free(data);
    return 0;
}
