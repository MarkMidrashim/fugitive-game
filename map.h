// Libs
#include <stdbool.h>

//Defines
#define HERO '@'
#define GHOST 'F'

#define FREE_SPACE_MOVIMENT '.'
#define HORIZONTAL_LIMIT '-'
#define VERTICAL_LIMIT '|'

// Structs
struct map {
	char** array;
	int lines, columns;
};

typedef struct map MAP;

struct position {
	int x, y;
};

typedef struct position POSITION;

// Methods
void loadMap(MAP* map, char* fileLevel);
void memoryAllocation(MAP* map);
void clearMap(MAP* map);
void showMap(MAP* map);

bool findHero(MAP* map, POSITION* position, char hero);
bool validateMoveInMap (MAP* map, int x, int y);
bool isEmpty(MAP* map, int x, int y);
void moveInMap(MAP* map, int xorigin, int yorigin, int xdestiny, int ydestiny);
void copyMap(MAP* destinyMap, MAP* originMap);
bool canMove(MAP* map, char character, int x, int y);
bool isLimitMap (MAP* map, int x, int y);
bool isCharacter (MAP* map, char character, int x, int y);