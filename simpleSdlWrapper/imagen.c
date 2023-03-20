#include "SDL.h"
#include "graphics.h"
#include "imagen.h"
#include <stdio.h>
#include "./includes/screens/game.h"

typedef struct Img {
	int id;
	SDL_Surface* image;
	SDL_Texture* texture;
	SDL_Rect dest;
} IMG;

IMG images[MAX_IMG];
int imageCount=0;
int id=0;

int loadImage(char* fileName, int windowId) {
	int colorkey;
	SDL_Surface* surface;
	SDL_Renderer* gRenderer = getRenderer(windowId);
	if (imageCount < MAX_IMG) {
		surface = SDL_LoadBMP(fileName);
		if (surface == NULL) {
			fprintf(stderr, "[ERROR]-> Couldn't load %s: %s\n", fileName, SDL_GetError());
			return -1;
		}
		else {
			colorkey = SDL_MapRGB(surface->format, 255, 0, 255);
			SDL_SetColorKey(surface, SDL_TRUE, colorkey);
			images[imageCount].texture = SDL_CreateTextureFromSurface(gRenderer, surface);
			images[imageCount].dest.x = images[imageCount].dest.y = 0;
			images[imageCount].dest.w = surface->w;
			images[imageCount].dest.h = surface->h;
			SDL_FreeSurface(surface);
			images[imageCount].id = id;
			imageCount++;
			id++;
		}
	}
	else {
		printf("[WARNING]-> MAX_IMG reached. Check imagen.h\n");
		return -1;
	}

	return id - 1;
}

int findImagePosition(int id) {
	int i = 0;
	for (i = 0; i < imageCount; i++) {
		if (id == images[i].id) return i;
	}
	return -1;
}

void moveImage(int numImg, int x, int y) {
	int id = findImagePosition(numImg);
	images[id].dest.x = x;
	images[id].dest.y = y;
}

void deleteImage(int id) {
	int i=0,pos=0;
	pos= findImagePosition(id);
	SDL_DestroyTexture(images[pos].texture);
	for ( i= pos ; i < imageCount ; i++) {
		images[i] = images[i+1];
	}
	imageCount--;
}

void drawImages(int windowId) {
	int i = 0;
	for (i = 0; i < imageCount; i++) {
		drawImage(images[i].texture, &images[i].dest, windowId);
	}
}

int getImageCount() { return imageCount; };