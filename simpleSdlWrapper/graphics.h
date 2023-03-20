#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "SDL.h"

#define MAX_WINDOWS 5
#define COLOR_GRAY 155, 155, 155

typedef struct pos {
	float x;
	float y;
} POS;

SDL_Renderer* gRenderer[MAX_WINDOWS];

SDL_Renderer* getRenderer(int sg);

int initializeSDL();
int createWindow(char name[], int width, int height, Uint32 flags);
void hideWindow(int windowNum);
void showWindow(int windowNum);
void clearWindow(int windowNum);
void reloadWindow(int windowNum);
void destroyWindow(int windowNum);
void nameWindow(int windowNum, char* title);

int drawImage(SDL_Texture* texture, SDL_Rect* pDest, int windowNum);

void setDrawingColor(int red, int green, int blue);
void drawPoint(int x, int y, int sg);
void drawLine(int x1, int y1, int x2, int y2, int sg);
void drawCircle(POS center, int radius, int windowId);
/*	Given the center position, the angle and the distance from the center, it returns
	the points of a circunference. If repeatedly used to draw different points it can be used
	to draw a hole circunference.
*/
POS getCirclePoint(POS center, float angle, int radius);

int getScreenWidht();
int getScreenHeight();

#endif