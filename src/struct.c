#include "pokemon.h"

// check the field of the mon to return its content
int field_check(const char *field, cJSON *mon)
{
    if (strcmp(field, "id") == 0 || strcmp(field, "bst") == 0) {
        printf("%d\n", cJSON_GetObjectItem(mon, field)->valueint);
        return (0);
    }
    if (strcmp(field, "types") == 0 || strcmp(field, "abilities") == 0) {
        cJSON *arr = cJSON_GetObjectItem(mon, field);
        for (int i = 0; i < cJSON_GetArraySize(arr); i++) {
            cJSON *tmp = cJSON_GetArrayItem(arr, i);
            printf("%s\n", tmp->valuestring);
        }
        return (0);
    }
    if (strcmp(field, "base_stats") == 0) {
        cJSON *stats = cJSON_GetObjectItem(mon, field);
        cJSON *stat;

        cJSON_ArrayForEach(stat, stats) {
            printf("%s: %d\n", stat->string, stat->valueint);
        }
        return (0);
    }
    return (1);
}

void fill2struct(mon_s *mon, cJSON *object)
{
    cJSON   *tmp;
    cJSON   *arr;
    int     i;

    i = 0;
    tmp = cJSON_GetObjectItem(object, "name");
    mon->name = tmp->valuestring;
    printf("name = %s\n", mon->name);
    tmp = cJSON_GetObjectItem(object, "id");
    mon->id = tmp->valueint;
    printf("id = %d\n", mon->id);
    tmp = cJSON_GetObjectItem(object, "types");
    printf("types = ");
    arr = cJSON_GetArrayItem(tmp, i);
    tmp = NULL;
    cJSON_ArrayForEach(tmp, arr) {
        mon->types[i++] = arr->valuestring;
        printf("%s\n", mon->types[i]);
    }
    tmp = cJSON_GetObjectItem(object, "abilities");
    printf("abilities = ");
    cJSON *cnt = cJSON_GetArrayItem(tmp, i);
    mon->abilities[i] = cnt->valuestring;
    printf("%s\n", mon->abilities[i]);
}
