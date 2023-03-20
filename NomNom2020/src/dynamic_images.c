#include "./includes/dynamic_images.h"
#include "./includes/images.h"
#include <stdlib.h>
#include <string.h>

DYNAMIC_IMG iniatializeDynamicImage() {
	DYNAMIC_IMG image;
	image.spriteSelected = 1;
	image.fileName = (char*)malloc(MAX_IMG_FILENAME_LENGTH * sizeof(char));
	image.clock = clock();
	return image;
}

void resetDynamicImageSprite(DYNAMIC_IMG* image, int imageSpriteNumber) {
	if (imageSpriteNumber == image->spriteSelected) image->spriteSelected = 1;
}

void selectCoinSprite(int coinSprite, char* coinFileName) {
	switch (coinSprite) {
		case 1: strcpy_s(coinFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_COIN1); break;
		case 2: strcpy_s(coinFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_COIN2); break;
		case 3: strcpy_s(coinFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_COIN3); break;
		case 4: strcpy_s(coinFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_COIN4); break;
		case 5: strcpy_s(coinFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_COIN5); break;
		case 6: strcpy_s(coinFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_COIN6); break;
		case 7: strcpy_s(coinFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_COIN7); break;
	}
}

void selectPlanetSprite(int planetSprite, char* planetFileName) {
	switch (planetSprite) {
		case 1: strcpy_s(planetFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_PLANET1); break;
		case 2: strcpy_s(planetFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_PLANET2); break;
		case 3: strcpy_s(planetFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_PLANET3); break;
		case 4: strcpy_s(planetFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_PLANET4); break;
	}
}

void selectAlvaroSprite(int alvaroSprite, char* alvaroFileName) {
	switch (alvaroSprite) {
		case 1: strcpy_s(alvaroFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_ALVARO1); break;
		case 2: strcpy_s(alvaroFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_ALVARO2); break;
		case 3: strcpy_s(alvaroFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_ALVARO3); break;
		case 4: strcpy_s(alvaroFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_ALVARO4); break;
		case 5: strcpy_s(alvaroFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_ALVARO5); break;
		case 6: strcpy_s(alvaroFileName, MAX_IMG_FILENAME_LENGTH, IMAGE_ALVARO6); break;
	}
}
