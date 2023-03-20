#ifndef GAME_H
#define GAME_H

#include <Windows.h>
#include "graphics.h"

#define BASE_SHOT_RATE 0.8			// 1 shot every 0.8 seconds
#define BASE_ALVARO_SPEED 0.4

#define POS_0 0, 0
#define POS_OUT -1000, -1000

#define MAX_SHOT_COUNT 70
#define SHOT_ANGLE_PRECISION 120

#define COIN_REFRESH_INTERVAL 0.09
#define COIN_ORBIT_RADIUS 300

#define PLANET_REFRESH_INTERVAL 0.3

#define ALVARO_REFRESH_INTERVAL 0.2

#define RIGHT TRUE
#define LEFT FALSE

typedef struct game_object {
	POS pos;
	int imageId;
} GAME_OBJECT;

typedef struct shot {
	GAME_OBJECT obj;
	char* shotFileName;
	float shotAngle;
	int shotDistance;
} SHOT;

void updateShotPositions(int shotCount, SHOT* shots, int shotSpeed);

/* Search for collisions with the coins and return total points */
int getCollisionsCoins(int coinCount, GAME_OBJECT* coins, GAME_OBJECT alvaro, int alvaroPoints);

/* Search for collisions with the shots and return life left */
int getCollisionsShots(int shotCount, SHOT* shots, GAME_OBJECT alvaro, int alvaroLife);

/* returns the remaining life ammount (0 for a lost run) */
int game(int level);

/* Given two object's positions and their sizes, returns if they collide */
boolean isCollision(POS pos1, int sizeX1, int sizeY1, POS pos2, int sizeX2, int sizeY2);

/* retuns true if it moves clockwise. Given the current direction it chooses to switch it according to a keyboardEvent (spacebar | left click) */
boolean getAlvaroDirection(boolean alvaroDirection, int keyboardEvent);

/* returns a POS object */
POS setPosition(float x, float y);

/* Randomly selects a shot image, witch can be of 8 different colors */
void randomShotSelector(char *shotFileName);

/* Randomly selects an angle around the player (to shoot at) */
float randomShotAngleSelector(float alvaroAngle);

/* Makes a copy of a SHOT object */
void shotCopy(SHOT* destination, SHOT* source);

/* returns shotCount. Deletes a SHOT from an array of them */
int deleteShot(SHOT* shots, int shotCount, int shotToDelete);

/* A pause screen witch stops the game */
int pause();

/* A save screen displayed when no life is remaining. */
void save(int alvaroPoints, int alvaroLife, int level);

/* A screen displayed to act as a TextField. Used in save(..); function */
void getText(char* text, int x, int y, int sg);

#endif