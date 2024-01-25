#include "game.h"

//handle game state
int checkGameState(int gridsum[][2], int gridsumdia[], bool empty, int scores[])
{
	if (scores[0] == 3 || scores[1] == 3)
		return EndGame;
	if (empty)
	{
		for (int y = 0; y < 3; ++y)
		{
			for (int x = 0; x < 2; ++x)
			{
				if (gridsum[y][x] == 6 || gridsumdia[x] == 6) return CrossWin;
				else if (gridsum[y][x] == 15 || gridsumdia[x] == 15)return OWin;
			}
		}
	}
	else
		return Tie;
}
//reset grid status to empty cells
int resetGrid(int gridsum[][2], int gridsumdia[], Cell grid[][3], bool empty)
{
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			grid[y][x].status = 0;
		}
	}
	for (int i = 0; i < 2; i++)gridsumdia[i] = 0;
	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 2; x++)gridsum[y][x] = 0;
	return InGame;
}
//increment scores when a player win
void scoreHandler(int scores[], int gameState)
{
	if (gameState == CrossWin)scores[0]++;
	else if (gameState == OWin)scores[1]++;
}
//reset scores to zero
void resetScore(int scores[])
{
	for (int i = 0; i < 2; i++)
		if (scores[i] == 3)
		{
			scores[i] = 0;
		}
}