// Libs
#include <stdbool.h>

// Defines
#define DIRECTION_LEFT 'a'
#define DIRECTION_UP 'w'
#define DIRECTION_DOWN 's'
#define DIRECTION_RIGHT 'd'

// Methods
bool isDirection(char direction);
void move(char direction);
bool finish();
void ghosts();
bool movingGhost(int xcurrent, int ycurrent, int* xdestiny, int* ydestiny);