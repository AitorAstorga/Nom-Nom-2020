#ifndef SCREENS_H
#define SCREENS_H

#include <Windows.h>
#include "./includes/screens/menu.h"
#include "./includes/screens/levels.h"
#include "./includes/screens/challenges.h"
#include "./includes/screens/shop.h"
#include "./includes/screens/game.h"
#include "includes/screens/leaderboard.h"

#define EXIT 0
#define MENU 1
#define LEVELS 2
#define CHALLENGES 3
#define SHOP 4
#define GAME 5
#define LEADERBOARD 6

void initializeMainWindow();
int setMainWindow(int screen);
void setMainWindowType(int screen);
void resetMainWindow(int screen);
int getScreenWindowType(int screen);
boolean isResettable(int screen);

POS getWindowCenterPos();
int getWindowId();

#endif