#pragma once
#include <stdbool.h>
#include "grid.h"

enum {
	CrossWin = 1,
	OWin = 2,
	Tie = 0,
	InGame = 3,
	EndGame = 4
};

int checkGameState(int gridsum[][2],int gridsumdia[], bool empty, int scores[]);
int resetGrid(int gridsum[][2], int gridsumdia[], Cell grid[][3], bool empty);
void scoreHandler(int scores[],int gameState);
void resetScore(int scores[]);