#include <stdio.h>
#include "./includes/screens/screens.h"
#include "graphics.h"
#include "imagen.h"

int main(int argc, char* argv[]) {
	int level = 1;
	int selection = MENU;

	initializeSDL();
	initializeMainWindow();
	setDrawingColor(COLOR_GRAY);

	while (selection != EXIT) {
		switch (selection) {
			case MENU:
				setMainWindow(MENU);
				selection = menu();
				level = 1;
				break;
			case LEVELS:
				setMainWindow(LEVELS);
				selection = levels();
				break;
			case CHALLENGES:
				setMainWindow(CHALLENGES);
				selection = challenges();
				break;
			case SHOP:
				setMainWindow(SHOP);
				shop();
				selection = MENU;
				break;
			case GAME:
				setMainWindow(GAME);
				while (game(level++) > 0);
				selection = MENU;
				break;
			case LEADERBOARD:
				setMainWindow(LEADERBOARD);
				leaderboard();
				selection = MENU;
				break;
			case EXIT:
				break;
		}
		if (getImageCount() > 0) printf("[WARNING]-> un-deleted images. imageCount: %i", getImageCount());
	}

	SDL_Quit();
	
	return 0;
}
