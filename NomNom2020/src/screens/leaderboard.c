#include "includes/screens/leaderboard.h"
#include <stdio.h>
#include "text.h"
#include "./includes/screens/screens.h"
#include <ebentoak.h>

#define MAX_LEADERBOARD 10

void leaderboard() {
	FILE *game, * gamesRegistry;
	char gameFile[128];
	int gameCount = 0;
	char gameSaveNames[MAX_LEADERBOARD][128];
	int keyboardEvent = 0;

	fopen_s(&gamesRegistry, "savedGames//gamesRegistry.txt", "r");
	if (gamesRegistry != NULL) {
		do {
			fgets(gameSaveNames[gameCount], sizeof(*gameSaveNames), gamesRegistry);
			for (int i = 0; i < 128; i++) {
				if (gameSaveNames[gameCount][i] == '\n') {
					gameSaveNames[gameCount][i] = '\0';
					break;
				}
			}
			if (feof(gamesRegistry)) break;
			gameCount++;
		} while (gameCount < MAX_LEADERBOARD);

		for (int i = 0; i < gameCount; i++) {
			printf("%s", gameSaveNames[i]);
			leaderboardFormat(gameSaveNames[i], i*3);
		}
		reloadWindow(getWindowId());
		
		while (keyboardEvent != TECLA_ESCAPE) {
			keyboardEvent = getEvent();
			fclose(gamesRegistry);
		}
	}
}

void leaderboardFormat(char* gameSaveName, int gap) {
	FILE* game;
	char format[128];

	char gameName[128];
	char gameLevel[128];
	char gamePoints[128];
	char alvaroLife[128];

	SDL_Color textColor = { 0XFF, 0XFF, 0XFF };
	textInit(20);

	char route[128] = "savedGames//";
	strcat(route, gameSaveName);
	fopen_s(&game, route, "r");

	if (game != NULL) {
		fgets(gameName, 128, game); deleteLastChar(gameName);
		fgets(gameLevel, 128, game); deleteLastChar(gameLevel);
		fgets(gamePoints, 128, game); deleteLastChar(gamePoints);
		fgets(alvaroLife, 128, game); deleteLastChar(alvaroLife);

		writeText(50, 80 + (20 * gap), gameName, getWindowId(), textColor);
		writeText(350, 80 + (20 * gap), gameLevel, getWindowId(), textColor);
		writeText(550, 80 + (20 * gap), gamePoints, getWindowId(), textColor);
		writeText(750, 80 + (20 * gap), alvaroLife, getWindowId(), textColor);
		
		reloadWindow(getWindowId());
		fclose(game);
		
	}

	Sleep(100);
}

void deleteLastChar(char str[]) {
	int i = 0;
	do {
		i++;
		if (str[i] == '\n') str[i] = '\0';
	} while (str[i] != '\n' && i < 128);
}
