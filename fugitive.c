// Libs
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "time.h"
#include "fugitive.h"
#include "map.h"

// Global's properties
MAP map;
POSITION hero;

/**
 * Ghost move in the map
 * Random moving ghost
 * @param int xcurrent
 * @param int ycurrent
 * @param int* xdestiny
 * @param int* ydestiny
 */
bool movingGhost(int xcurrent, int ycurrent, int* xdestiny, int* ydestiny) {
	int options[4][2] = {
		{xcurrent, ycurrent+1},
		{xcurrent+1, ycurrent},
		{xcurrent, ycurrent-1},
		{xcurrent-1, ycurrent},
	};

	srand(time(0));

	for (int i = 0; i < 10; i++) {
		int position = rand() % 4;

		if (canMove(&map, GHOST, options[position][0], options[position][1])) {
			*xdestiny = options[position][0];
			*ydestiny = options[position][1];
			return true;
		}
	}

	return false;
}

/**
 * Ghost
 */
void ghosts() {
	MAP copy;
	copyMap(&copy, &map);

	for (int i = 0; i < map.lines; i++) {
		for (int j = 0; j < map.columns; j++) {
			if (map.array[i][j] == GHOST) {
				int xdestiny, ydestiny;

				if (movingGhost(i, j, &xdestiny, &ydestiny)) {
					moveInMap(&map, i, j, xdestiny, ydestiny);
				}
			}
		}
	}

	clearMap(&copy);
}

/**
 * Validate if is direction
 * @param char direction
 */
bool isDirection(char direction) {
	return direction == DIRECTION_LEFT || 
			direction == DIRECTION_UP || 
			direction == DIRECTION_DOWN || 
			direction == DIRECTION_RIGHT;
}

/**
 * Move 
 * @param char direction
 */
void move(char direction) {
	if (!isDirection(direction)) return;
	int nextx = hero.x, nexty = hero.y;
	
	switch (direction) {
		case DIRECTION_LEFT:
			nexty--;
			break;
		case DIRECTION_UP:
			nextx--;
			break;
		case DIRECTION_DOWN:
			nextx++;
			break;
		case DIRECTION_RIGHT:
			nexty++;
			break;
	}
	
	if (!canMove(&map, HERO, nextx, nexty)) return;
	moveInMap(&map, hero.x, hero.y, nextx, nexty);

	// Update moviments of hero
	hero.x = nextx;
	hero.y = nexty;
}

/**
 * Finish 
 */
bool finish() {
	POSITION position;

	bool isWin = !findHero(&map, &position, HERO);
	bool isLose = !findHero(&map, &position, GHOST);

	return isWin || isLose;
}

int main() {
	// Select map
	char* fileLevel = "C:\\Users\\Wilson\\Documents\\FugitiveGame\\map.txt";

	loadMap(&map, fileLevel);
	findHero(&map, &hero, HERO);
	
	do {
		system("cls");
		showMap(&map);
		
		char command;
		scanf(" %c", &command);

		move(command);
		ghosts();
	} while(!finish());

	clearMap(&map);
}