#ifndef DYNAMIC_IMAGES_H
#define DYNAMIC_IMAGES_H

#include <time.h>

typedef struct dynamic_img {
	int spriteSelected;
	char* fileName;
	clock_t clock;
} DYNAMIC_IMG;

DYNAMIC_IMG iniatializeDynamicImage();
void resetDynamicImageSprite(DYNAMIC_IMG* image, int imageSpriteNumber);
void selectCoinSprite(int coinSprite, char* coinFileName);
void selectPlanetSprite(int planetSprite, char* planetFileName);
void selectAlvaroSprite(int alvaroSprite, char* alvaroFileName);

#endif