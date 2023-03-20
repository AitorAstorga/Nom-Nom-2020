#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define GRAPHICS

#include "SDL_ttf.h"

#include "./includes/images.h"
#include "graphics.h"

SDL_Window* window[MAX_WINDOWS] = { NULL };

int colorR, colorG, colorB;
int windowCount;

SDL_Renderer* getRenderer(int windowNum) { return gRenderer[windowNum]; }

int initializeSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "[ERROR]-> SDL couldn't be initialized: %s\n", SDL_GetError());
		return 0;
	}
	atexit(SDL_Quit);
	return 1;
}

int createWindow(char name[], int width, int height, Uint32 flags) {
	if (windowCount == (int)NULL) windowCount = 1;
	else windowCount++;
	window[windowCount] = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
	SDL_SetWindowIcon(window[windowCount], SDL_LoadBMP(IMAGE_MAIN_ICON));
	if (window[windowCount] == NULL) {
		fprintf(stderr, "[ERROR]-> Window can't be created: %s\n", SDL_GetError());
		return 0;
	}
	gRenderer[windowCount] = SDL_CreateRenderer(window[windowCount], -1, SDL_RENDERER_ACCELERATED);
	TTF_Init();
	atexit(TTF_Quit);
	return windowCount;
}

void hideWindow(int windowNum) {
	SDL_HideWindow(window[windowNum]);
}

void showWindow(int windowNum) {
	SDL_ShowWindow(window[windowNum]);
	SDL_RaiseWindow(window[windowNum]);
}

void clearWindow(int windowNum) {
	SDL_SetRenderDrawColor(gRenderer[windowNum], 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(gRenderer[windowNum]);
}

void reloadWindow(int windowNum) {
	SDL_RenderPresent(gRenderer[windowNum]);
}

void destroyWindow(int windowNum) {
	SDL_DestroyWindow(window[windowNum]);
	windowCount--;
}

void nameWindow(int windowNum, char *title) {
	SDL_SetWindowTitle(window[windowNum], title);
}

int drawImage(SDL_Texture* texture, SDL_Rect* pDest, int windowNum) {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = pDest->w;
	src.h = pDest->h;
	SDL_RenderCopy(gRenderer[windowNum], texture, &src, pDest);
	return 0;
}

void setDrawingColor(int red, int green, int blue) {
  colorR = red;
  colorG = green;
  colorB = blue;
}

void drawPoint(int x, int y, int sg) {
	SDL_SetRenderDrawColor(gRenderer[sg], colorR, colorG, colorB, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(gRenderer[sg], x, y);
}

void drawLine(int x1, int y1, int x2, int y2, int sg) {
  SDL_SetRenderDrawColor(gRenderer[sg], colorR, colorG, colorB, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(gRenderer[sg], x1, y1, x2, y2);
}

void drawCircle(POS center, int radius, int windowId) {
	for (int i = 0; i < 360; i++) {
		POS pointPos = getCirclePoint(center, (float)i, radius);
		drawPoint((int)pointPos.x, (int)pointPos.y, windowId);
	}
}

double degreesToRadians(double degrees) {
	return degrees * M_PI / 180;
}

POS getCirclePoint(POS center, float angle, int radius) {
	POS pos;
	pos.x = ((float)radius * (float)cos(degreesToRadians((double)angle))) + center.x;
	pos.y = center.y - ((float)radius * (float)sin(degreesToRadians((double)angle)));
	return pos;
}

int getScreenWidht() {
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	return DM.w;
}

int getScreenHeight() {
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	return DM.h;
}