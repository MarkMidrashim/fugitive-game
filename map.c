// Libs
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "map.h"

/**
 * Can move in the map
 * @param MAP* map
 * @param char character
 * @param int x
 * @param int y
 */
bool canMove(MAP* map, char character, int x, int y) {
	return validateMoveInMap(map, x, y) && !isLimitMap(map, x, y) && !isCharacter(map, character, x, y);
}

/**
 * Copy Map
 * @param MAP destiny
 * @param MAP origin
 */
void copyMap(MAP* destiny, MAP* origin) {
	destiny->lines = origin->lines;
	destiny->columns = origin->columns;

	memoryAllocation(destiny);

	for (int i = 0; i < origin->lines; i++) {
		strcpy(destiny->array[i], origin->array[i]);
	}
}

/**
 * Move in the map
 * @param MAP map
 * @param int xorigin
 * @param int yorigin
 * @param int xdestiny
 * @param int ydestiny
 */
void moveInMap(MAP* map, int xorigin, int yorigin, int xdestiny, int ydestiny) {
	char character = map->array[xorigin][yorigin];
	map->array[xdestiny][ydestiny] = character;
	map->array[xorigin][yorigin] = FREE_SPACE_MOVIMENT;
}

/**
 * Validate 
 * @param MAP map
 * @param int x
 * @param int y
 */
bool isEmpty(MAP* map, int x, int y) {
	if (map->array[x][y] != FREE_SPACE_MOVIMENT) return false;
	return true;
}

/**
 * Validate move in map
 * @param MAP map
 * @param int x
 * @param int y
 */
bool validateMoveInMap (MAP* map, int x, int y) {
	if (x >= map->lines) return false;
	if (y >= map->columns) return false;
	return true;
}

/**
 * Validate move in map
 * @param MAP map
 * @param int x
 * @param int y
 */
bool isLimitMap (MAP* map, int x, int y) {
	if (map->array[x][y] == VERTICAL_LIMIT || map->array[x][y] == HORIZONTAL_LIMIT) return true;
	return false;
}

/**
 * Validate move in map
 * @param MAP map
 * @param char character
 * @param int x
 * @param int y
 */
bool isCharacter (MAP* map, char character, int x, int y) {
	if (map->array[x][y] == HERO) return true;
	return false;
}

/**
 * Find hero in the map
 * @param MAP map
 * @param POSITION* position
 * @param char hero
 */
bool findHero(MAP* map, POSITION* position, char hero) {
	for (int i = 0; i < map->lines; i++) {
		for (int j = 0; j < map->columns; j++) {
			if (map->array[i][j] == hero) {
				position->x = i;
				position->y = j;
				return true;
			}
		}
	}

	return false;
}

/**
 * Load map
 * @param MAP map
 * @param char* fileLevel
 */
void loadMap(MAP* map, char* fileLevel) {
	FILE *database;
	
	database = fopen(fileLevel, "r");
	if (database == 0) {
		printf("Map is not available!\n");
        exit(1);
    }
	
	fscanf(database, "%d %d", &map->lines, &map->columns);
	memoryAllocation(map);
	
	for (int i = 0; i < map->lines; i++) {
        fscanf(database, "%s", map->array[i]);
    }

    fclose(database);
}

/**
 * Memory Allocation
 * @param MAP map
 */
void memoryAllocation(MAP* map) {
	map->array = malloc(sizeof(char*) * map->lines);
    for (int i = 0; i < map->lines; i++) {
		map->array[i] = malloc(sizeof(char) * map->columns + 1);
    }
}

/**
 * Clear map
 * @param MAP map
 */
void clearMap(MAP* map) {
	for (int i = 0; i < map->lines; i++) {
		free(map->array[i]);
	}
	
	free(map->array);
}

/**
 * Show map
 * @param MAP map
 */
void showMap(MAP* map) {
	for (int i = 0; i < map->lines; i++) {
        printf("%s\n", map->array[i]);
    }
}