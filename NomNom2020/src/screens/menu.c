#include "./includes/screens/game.h"
#include <SDL.h>
#include "graphics.h"
#include "./includes/images.h"
#include "imagen.h"
#include "ebentoak.h"
#include "./includes/screens/screens.h"

int menu() {
	int selection = -1;
	int backgroundImageId;
	int keyboardEvent;
	POSIZIOA mousePos;

	backgroundImageId = loadImage(IMAGE_MENU, getWindowId());
	moveImage(backgroundImageId, POS_0);
	drawImages(getWindowId());
	reloadWindow(getWindowId());

	while (selection == -1) {
		keyboardEvent = getEvent();
		if (keyboardEvent == MOUSE_KEY_LEFT) {
			mousePos = getMousePos();
			if (mousePos.y > 23 && mousePos.y < 268) selection = GAME;
			if (mousePos.y > 276 && mousePos.y < 516) selection = LEADERBOARD;
			if (mousePos.y > 525) selection = EXIT;
		}
	}
	deleteImage(backgroundImageId);
	return selection;
}
