#include "graphics.h"
#include "imagen.h"
#include "./includes/screens/screens.h"
#include "./includes/screens/game.h"

#define WINDOW_NAME_LEVELS "Nom Nom 2020 - LEVELS"
#define WINDOW_NAME_CHALLENGES "Nom Nom 2020 - CHALLENGES"
#define WINDOW_NAME_SHOP "Nom Nom 2020 - SHOP"
#define WINDOW_NAME_GAME "Nom Nom 2020"

#define WINDOW_SIZE_COEFFICIENT_X 0.6 // % of the screen width that will be occupied
#define WINDOW_SIZE_COEFFICIENT_Y 0.8 // % of the screen height that will be occupied

#define BORDERLESS_WINDOW 1
#define NORMAL_WINDOW 2

POS windowCenterPos;
int windowSizeX;
int windowSizeY;
int windowId;
int windowType;
boolean windowExists;

void initializeMainWindow() {
	windowType = BORDERLESS_WINDOW;
	windowSizeX = (int)(getScreenWidht() * WINDOW_SIZE_COEFFICIENT_X);
	windowSizeY = (int)(getScreenHeight() * WINDOW_SIZE_COEFFICIENT_Y);
	if (windowSizeX != 921 || windowSizeY != 691) {
		printf("[WARNING]-> Screen bounds are different from the creator's PC! 1536,864\n");
	}
	windowCenterPos = setPosition((float)windowSizeX / 2, (float)windowSizeY / 2);
	windowExists = FALSE;
}

char* setMainWindowName(int screen) {
	switch (screen) {
		default: return "";
		case LEVELS: return WINDOW_NAME_GAME;
		case CHALLENGES: return WINDOW_NAME_LEVELS;
		case SHOP: return WINDOW_NAME_SHOP;
		case GAME: return WINDOW_NAME_GAME;
	}
}

int setMainWindow(int screen) {
	int resettable = isResettable(screen);
	setMainWindowType(screen);

	if (resettable) resetMainWindow(screen);
	else {
		if (windowExists) destroyWindow(getWindowId());
		if (windowType == BORDERLESS_WINDOW) {
			windowId = createWindow(setMainWindowName(screen), windowSizeX, windowSizeY, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
		}
		else {
			windowId = createWindow(setMainWindowName(screen), windowSizeX, windowSizeY, SDL_WINDOW_SHOWN);
		}
		windowExists = TRUE;
	}
	
	return TRUE;
}

void setMainWindowType(int screen) {
	windowType = getScreenWindowType(screen);
}

int getScreenWindowType(int screen) {
	int screenWindowType = NORMAL_WINDOW;

	if (screen == MENU || screen == LEADERBOARD) {
		screenWindowType = BORDERLESS_WINDOW;
	}
	return screenWindowType;
}

boolean isResettable(int screen) {
	if (!windowExists) return FALSE;
	return windowType == getScreenWindowType(screen);
}

void resetMainWindow(int screen) {
	clearWindow(getWindowId());
	nameWindow(getWindowId(), setMainWindowName(screen));
}

POS getWindowCenterPos() { return windowCenterPos; };

int getWindowId() { return windowId; };
