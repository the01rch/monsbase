#ifndef POKEMON_H
#define POKEMON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
	int			id;
	const char	*name;
	const char	*types[2];
	const char	*abilities[3];
	int			hp;
	int			defense;
	int			attack;
	int			sp_attack;
	int			sp_defense;
	int			speed;
	int			bst;
	int			*moves;
} mon_s;

char *get_data(const char *path);
bool json_parser(const char *path, const char *object);

#endif
