#include "./includes/screens/game.h"
#include "./includes/screens/screens.h"
#include "./includes/images.h"
#include "./includes/dynamic_images.h"
#include <stdio.h>
#include "graphics.h"
#include "imagen.h"
#include "ebentoak.h"
#include "text.h"

#define SAVE_GAME 1
#define ALVARO_MAX_LIFE 5

void updateShotPositions(int shotCount, SHOT* shots, int shotSpeed) {
	for (int i = 0; i < shotCount; i++) {
		(shots + i)->obj.pos = getCirclePoint(getWindowCenterPos(), (shots + i)->shotAngle, (shots + i)->shotDistance);
		(shots + i)->shotDistance -= shotSpeed;
		//Delete already gone shots
		if ((shots + i)->shotDistance > COIN_ORBIT_RADIUS + 100) {
			shotCount = deleteShot(shots, shotCount, i);
		}
	}
}

int getCollisionsCoins(int coinCount, GAME_OBJECT* coins, GAME_OBJECT alvaro, int alvaroPoints) {
	for (int i = 0; i < coinCount; i++) {
		if (isCollision(alvaro.pos, RADIUS_ALVARO_X, RADIUS_ALVARO_Y, (coins + i)->pos, SIZE_COINS_X, SIZE_COINS_Y)) {
			(coins + i)->pos = setPosition(POS_OUT);
			alvaroPoints++;
		}
	}
	return alvaroPoints;
}

int getCollisionsShots(int shotCount, SHOT* shots, GAME_OBJECT alvaro, int alvaroLife) {
	for (int i = 0; i < shotCount; i++) {
		if (isCollision(alvaro.pos, RADIUS_ALVARO_X, RADIUS_ALVARO_Y, (shots + i)->obj.pos, SIZE_SHOTS_X, SIZE_SHOTS_Y)) {
			shotCount = deleteShot(shots, shotCount, i);
			alvaroLife--;
		}
	}
	return alvaroLife;
}

int game(int level) {
	printf("%i\n", level);
	/* VARIABLES */
	int shotCount = 0;
	float shotRate = BASE_SHOT_RATE - level*0.05;
	int shotSpeed = 1 + (int)(level*0.65);
	clock_t shotRateClock;

	SHOT *shots = (SHOT*)malloc(MAX_SHOT_COUNT * sizeof(SHOT));
	for (int i = 0; i < MAX_SHOT_COUNT; i++) {
		(shots + i)->shotFileName = (char*)malloc(MAX_IMG_FILENAME_LENGTH * sizeof(char));
	}

	int coinCount = level * 5;
	GAME_OBJECT *coins = (GAME_OBJECT*)malloc(coinCount * sizeof(GAME_OBJECT));
	DYNAMIC_IMG coinImg;

	GAME_OBJECT planet;
	DYNAMIC_IMG planetImg;

	GAME_OBJECT alvaro;
	DYNAMIC_IMG alvaroImg;
	float alvaroAngle = 90;
	float alvaroSpeed = 0.4F;
	boolean alvaroDirection = RIGHT;
	int alvaroPoints = 0;
	int alvaroLife = ALVARO_MAX_LIFE;

	int backgroundImageId;

	boolean isPause = FALSE;

	/* INITIALIZATION */
	shotRateClock = clock();
	coinImg = iniatializeDynamicImage();
	planetImg = iniatializeDynamicImage();
	alvaroImg = iniatializeDynamicImage();

	//Set each image's position
	for (int i = 0; i < coinCount; i++) {
		(coins + i)->pos = getCirclePoint(getWindowCenterPos(), (float)(360 / coinCount * (i + 1)), COIN_ORBIT_RADIUS);
	}
	planet.pos = getWindowCenterPos();
	alvaro.pos = getCirclePoint(getWindowCenterPos(), alvaroAngle, COIN_ORBIT_RADIUS);

	//Set the background image
	backgroundImageId = loadImage(IMAGE_BACKGROUND1, getWindowId());
	moveImage(backgroundImageId, POS_0);

	/* MAIN LOOP */
	while (alvaroPoints < coinCount && alvaroLife > 0) {
		/* GAME MATH */
		int keyboardEvent = getEvent();
		alvaroDirection = getAlvaroDirection(alvaroDirection, keyboardEvent);
		
		if (alvaroAngle > 360) alvaroAngle = 0;
		if (alvaroAngle < 0) alvaroAngle = 360;

		if (alvaroDirection == TRUE) alvaroAngle -= alvaroSpeed;
		if (alvaroDirection == FALSE) alvaroAngle += alvaroSpeed;

		alvaro.pos = getCirclePoint(getWindowCenterPos(), alvaroAngle, COIN_ORBIT_RADIUS);

		updateShotPositions(shotCount, shots, shotSpeed);

		//Get collisions
		alvaroPoints = getCollisionsCoins(coinCount, coins, alvaro, alvaroPoints);
		alvaroLife = getCollisionsShots(shotCount, shots, alvaro, alvaroLife);

		/* GRAPHICS */
		//Image's refresh intervals
		double coin_time_elapsed_in_seconds = (clock() - coinImg.clock) / (double)CLOCKS_PER_SEC;
		if (coin_time_elapsed_in_seconds >= COIN_REFRESH_INTERVAL) {
			coinImg.clock = clock();
			coinImg.spriteSelected++;
		}
		double planet_time_elapsed_in_seconds = (clock() - planetImg.clock) / (double)CLOCKS_PER_SEC;
		if (planet_time_elapsed_in_seconds >= PLANET_REFRESH_INTERVAL) {
			planetImg.clock = clock();
			planetImg.spriteSelected++;
		}

		double alvaro_time_elapsed_in_seconds = (clock() - alvaroImg.clock) / (double)CLOCKS_PER_SEC;
		if (alvaro_time_elapsed_in_seconds >= ALVARO_REFRESH_INTERVAL) {
			alvaroImg.clock = clock();
			alvaroImg.spriteSelected++;
		}

		//Shot fire-rate time intervals
		double shot_time_elapsed_in_seconds = (clock() - shotRateClock) / (double)CLOCKS_PER_SEC;
		if (shot_time_elapsed_in_seconds >= shotRate) {
			shotRateClock = clock();
			randomShotSelector((shots + shotCount)->shotFileName);
			(shots + shotCount)->shotAngle = randomShotAngleSelector(alvaroAngle);
			(shots + shotCount)->obj.pos = getWindowCenterPos();
			(shots + shotCount)->shotDistance = 0;
			shotCount++;
		}

		//Image's sprite reset
		resetDynamicImageSprite(&coinImg, SPRITE_NUMBER_COIN);
		resetDynamicImageSprite(&planetImg, SPRITE_NUMBER_PLANET);
		resetDynamicImageSprite(&alvaroImg, SPRITE_NUMBER_ALVARO);
		
		//Selecting image corresponding to it's cycle
		selectCoinSprite(coinImg.spriteSelected, coinImg.fileName);
		selectPlanetSprite(planetImg.spriteSelected, planetImg.fileName);
		selectAlvaroSprite(alvaroImg.spriteSelected, alvaroImg.fileName);

		//Image loading
		for (int i = 0; i < shotCount; i++) {
			(shots + i)->obj.imageId = loadImage((shots + i)->shotFileName, getWindowId());
			moveImage((shots + i)->obj.imageId, (int)(shots + i)->obj.pos.x - RADIUS_SHOTS_X, (int)(shots + i)->obj.pos.y - RADIUS_SHOTS_Y);
		}
		for (int i = 0; i < coinCount; i++) {
			(coins + i)->imageId = loadImage(coinImg.fileName, getWindowId());
			moveImage((coins + i)->imageId, (int)((coins + i)->pos).x - RADIUS_COINS_X, (int)((coins + i)->pos).y - RADIUS_COINS_Y);
		}
		planet.imageId = loadImage(planetImg.fileName, getWindowId());
		moveImage(planet.imageId, (int)planet.pos.x - RADIUS_PLANET_X, (int)planet.pos.y - RADIUS_PLANET_Y);
		alvaro.imageId = loadImage(alvaroImg.fileName, getWindowId());
		moveImage(alvaro.imageId, (int)alvaro.pos.x - RADIUS_ALVARO_X, (int)alvaro.pos.y - RADIUS_ALVARO_Y);

		//Screen refreshing
		drawImages(getWindowId());
		drawCircle(getWindowCenterPos(), COIN_ORBIT_RADIUS, getWindowId());
		reloadWindow(getWindowId());

		//Asking if the game must be paused (this is not asked previously as the images were not loaded yet)
		if (!isPause && keyboardEvent == TECLA_p)
			if (pause() == SAVE_GAME) save(alvaroPoints, alvaroLife, level);
		if (alvaroLife < 1) save(alvaroPoints, alvaroLife, level);

		if (keyboardEvent == TECLA_ESCAPE) alvaroLife = 0;

		//Deleting already used images from memory
		for (int i = 0; i < shotCount; i++) {
			deleteImage((shots + i)->obj.imageId);
		}
		for (int i = 0; i < coinCount; i++) {
			deleteImage((coins + i)->imageId);
		}
		deleteImage(planet.imageId);
		deleteImage(alvaro.imageId);
	}
	deleteImage(backgroundImageId);

	//Free allocated memory
	for (int i = 0; i < MAX_SHOT_COUNT; i++) free((shots + i)->shotFileName);
	free(shots);
	free(coins);
	free(coinImg.fileName);
	free(planetImg.fileName);
	free(alvaroImg.fileName);

	return alvaroLife;
}

POS setPosition(float x, float y) {
	POS pos;
	pos.x = x;
	pos.y = y;
	return pos;
}

boolean isCollision(POS pos1, int sizeX1, int sizeY1, POS pos2, int sizeX2, int sizeY2) {
	if (pos1.x < pos2.x + sizeX2 && pos1.x + sizeX1 > pos2.x &&
		pos1.y < pos2.y + sizeY2 && pos1.y + sizeY1 > pos2.y) return TRUE;
	return FALSE;
}

boolean getAlvaroDirection(boolean direction, int keyboardEvent) {
	if (keyboardEvent == KEY_SPACE) direction = !direction;
	if (keyboardEvent == MOUSE_KEY_LEFT) direction = !direction;
	return direction;
}

void randomShotSelector(char *shotFileName) {
	int random = rand() % 8;
	char *fileName = IMAGE_PINK_SHOT_SHOT;

	switch(random) {
		case 0: fileName = IMAGE_PINK_SHOT_SHOT; break;
		case 1: fileName = IMAGE_NOT_SO_BLUE_SHOT; break;
		case 2: fileName = IMAGE_RED_SHOT; break;
		case 3: fileName = IMAGE_ORANGE_SHOT; break;
		case 4: fileName = IMAGE_GREEN_SHOT; break;
		case 5: fileName = IMAGE_BLUE_SHOT; break;
		case 6: fileName = IMAGE_YELLOW_SHOT; break;
		case 7: fileName = IMAGE_LIME_SHOT; break;
	}
	strcpy_s(shotFileName, MAX_IMG_FILENAME_LENGTH * sizeof(char), fileName);
}

float randomShotAngleSelector(float alvaroAngle) {
	float randomAngle = alvaroAngle + ((rand() % SHOT_ANGLE_PRECISION) - SHOT_ANGLE_PRECISION/2);
	return randomAngle;
}

void shotCopy(SHOT *destination, SHOT *source) {
	destination->obj = source->obj;
	strcpy_s(destination->shotFileName, MAX_IMG_FILENAME_LENGTH, source->shotFileName);
	destination->shotAngle = source->shotAngle;
	destination->shotDistance = source->shotDistance;
}

int deleteShot(SHOT* shots, int shotCount, int shotToDelete) {
	for (int j = shotToDelete; j < shotCount - 1; j++) {
		shotCopy((shots + j), (shots + j + 1));
	}
	return --shotCount;
}

int pause() {
	int keyboardEvent = 0;
	while (keyboardEvent != TECLA_p && keyboardEvent != TECLA_s) {
		keyboardEvent = getEvent();
	}
	if (keyboardEvent == TECLA_s) return SAVE_GAME;

	return 0;
}

void save(int alvaroPoints, int alvaroLife, int level) {
	FILE *game, *gamesRegistry;
	char gameFile[128];
	char gameSaveName[128];

	SDL_Color textColor = { 0XFF, 0XFF, 0XFF };

	gameSaveName[0] = ' ';
	gameSaveName[1] = '\0';

	int imageIdSave = loadImage(IMAGE_SAVE, getWindowId());
	moveImage(imageIdSave, getWindowCenterPos().x - SIZE_SAVE_X/2, getWindowCenterPos().y - SIZE_SAVE_Y/2);
	drawImages(getWindowId());
	reloadWindow(getWindowId());
	
	textInit(30);
	getText(gameSaveName, getWindowCenterPos().x - SIZE_SAVE_X/2 + 20, getWindowCenterPos().y - SIZE_SAVE_Y/2, getWindowId());

	if (*gameSaveName != NULL) {
		sprintf_s(gameFile, 128, "savedGames//%s.txt", gameSaveName);
		fopen_s(&game, gameFile, "w");

		if (game != NULL) {
			fprintf(game, "NAME: %s\nLEVEL: %i\nPOINTS: %i\nLIFE: %i\n", gameSaveName, level, alvaroPoints, alvaroLife);
			fclose(game);
		}

		fopen_s(&gamesRegistry, "savedGames//gamesRegistry.txt", "a");
		if (gamesRegistry != NULL) {
			fprintf(gamesRegistry, "%s.txt\n", gameSaveName);
			fclose(gamesRegistry);
		}
	}
	deleteImage(imageIdSave);
}

void getText(char* text, int x, int y, int sg) {
	SDL_Color textColor = { 0XFF, 0XFF, 0XFF };
	int keyboardEvent;
	int letterCount = 0;
	do {
		keyboardEvent = getEvent();
		if (keyboardEvent == TECLA_ESCAPE) {
			*text = NULL;
			break;
		}
		if (letterCount < 16 && keyboardEvent >= 32 && keyboardEvent <= 126) {
			text[letterCount] = keyboardEvent;
			letterCount++;
			text[letterCount] = '\0';
			clearWindow(getWindowId());
			drawImages(getWindowId());
			drawCircle(getWindowCenterPos(), COIN_ORBIT_RADIUS, getWindowId());
			writeText(x, y, text, sg, textColor);
			reloadWindow(getWindowId());
		}
		if (keyboardEvent == 8) {//8 BACKSPACE (ezabatu) da
			if (letterCount > 0) {
				letterCount--;
				text[letterCount] = '\0';
				clearWindow(getWindowId());
				drawImages(getWindowId());
				drawCircle(getWindowCenterPos(), COIN_ORBIT_RADIUS, getWindowId());
				if (letterCount > 1) writeText(x, y, text, sg, textColor);
				reloadWindow(getWindowId());
			}
		}
	} while (keyboardEvent != TECLA_RETURN || letterCount < 1);
	if (*text != NULL) text[letterCount] = '\0';
}
