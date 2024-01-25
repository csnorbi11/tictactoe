#include <time.h>
#include <cstdlib>
#include "window.h"
#include "text.h"
#include "grid.h"
#include "game.h"


void textHandler(std::stringstream* gameStateText, std::stringstream* scoreText, std::stringstream* roundText, int player, int scores[], int gameState);
void textureDestroy(SDL_Texture* nameTextTexture, SDL_Texture* scoreTextTexture, SDL_Texture* stateTextTexture, SDL_Texture* roundTextTexture);
void logic(int* player, int* random, Cell grid[][3], int gridsum[][2], int gridsumdia[], bool* empty, int scores[], int* gameState);

int main(int argc, char* args[])
{
	srand(time(NULL));
	int random = rand() % 2;

	SDL_Event e;
	bool exit = init_game();

	SDL_Texture* gridTexture = loadImg("grid.png", g_Renderer);
	SDL_Texture* oTexture = loadImg("o.png", g_Renderer);
	SDL_Texture* xTexture = loadImg("x.png", g_Renderer);
	SDL_Texture* cellTexture[3][3] = { {NULL} };

	SDL_Point mousePos = { 0,0 };

	Cell grid[3][3];
	int gridsum[3][2] = { {0} };
	int gridsumdia[2];
	init_grid(grid);

	int player;
	if (random == 0)player = O;
	else player = CROSS;
	bool empty = true;
	int gameState = InGame;
	int scores[2] = { 0 };

	

	SDL_Texture* nameTextTexture = NULL;

	SDL_Texture* scoreTextTexture = NULL;
	std::stringstream scoreText;

	SDL_Texture* stateTextTexture = NULL;
	std::stringstream gameStateText;

	SDL_Texture* roundTextTexture = NULL;
	std::stringstream roundText;

	SDL_Texture* endGameTexture = NULL;
	std::stringstream endText;


	while (!exit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					exit = true;
					break;
				}
				break;
			case SDL_QUIT:
				exit = true;
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mousePos.x, &mousePos.y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				for (int y = 0; y < 3; ++y)
				{
					for (int x = 0; x < 3; ++x)
					{
						if (mousePos.x > grid[y][x].startPos.x && mousePos.x < grid[y][x].endPos.x &&
							mousePos.y>grid[y][x].startPos.y && mousePos.y < grid[y][x].endPos.y)
						{
							if (grid[y][x].status == EMPTY)
							{
								if (player == CROSS)
								{
									grid[y][x].status = player;
									player = O;
								}
								else
								{
									grid[y][x].status = player;
									player = CROSS;
								}
							}							
						}
					}
				}
				break;
			}
		}
		//handle game logic
		logic(&player, &random, grid, gridsum, gridsumdia, &empty, scores, &gameState);
		//handle textes
		textHandler(&gameStateText, &scoreText, &roundText, player, scores, gameState);
		//handle seperately to write out which player won the whole game
		if (gameState == EndGame)
			resetScore(scores);

		//prepare back buffer
		SDL_SetRenderDrawColor(g_Renderer, 8, 177, 207, 1);
		SDL_RenderClear(g_Renderer);

		//draw to backbuffer
		render_grid(grid, gridTexture, g_Renderer);
		render_cells(grid,xTexture,oTexture,cellTexture,g_Renderer);
		text(&nameTextTexture, "Tic-Tac-Toe", g_Font, { 0,0,0,255 }, { SCREEN_WIDTH / 2,(int)(SCREEN_HEIGHT * 0.02) }, g_Renderer);
		text(&scoreTextTexture, scoreText.str().c_str(), g_Font, { 0,0,0,255 }, { (int)(SCREEN_WIDTH * 0.25),(int)(SCREEN_HEIGHT * 0.12) }, g_Renderer);
		text(&stateTextTexture, gameStateText.str().c_str(), g_Font, { 0,0,0,255 }, { (int)(SCREEN_WIDTH * 0.35),(int)(SCREEN_HEIGHT * 0.21) }, g_Renderer);
		text(&roundTextTexture, roundText.str().c_str(), g_Font,{ 0,0,0,255 }, { (int)(SCREEN_WIDTH * 0.75),(int)(SCREEN_HEIGHT * 0.12) }, g_Renderer);


		//render backbuffer
		SDL_RenderPresent(g_Renderer);
		//delay the game if something happened
		if (gameState != InGame)
			SDL_Delay(3000);

		//destroy texts texture
		textureDestroy(nameTextTexture, scoreTextTexture, stateTextTexture, roundTextTexture);


	}
	
	

	free();

	return 0;
}

void textHandler(std::stringstream* gameStateText, std::stringstream* scoreText, std::stringstream* roundText, int player, int scores[], int gameState)
{
	gameStateText->str("");
	scoreText->str("");
	roundText->str("");
	*(scoreText) << scores[0] << ":" << scores[1];
	if (gameState == Tie)
		*(gameStateText) << "Tie";
	else if (gameState == EndGame)
	{
		if (scores[0] == 3)
			*(gameStateText) << "Cross won the game";
		else if (scores[1] == 3)
			*(gameStateText) << "O won the game";
	}
	else if (gameState == CrossWin)
		*(gameStateText) << "Cross won";
	else if (gameState == OWin)
		*(gameStateText) << "O won";
	else if (gameState == InGame)
		*(gameStateText) << "In Game";
	if (player == O)
		*(roundText) << "O";
	else if (player == CROSS)
		*(roundText) << "X";
}

void textureDestroy(SDL_Texture* nameTextTexture, SDL_Texture* scoreTextTexture, SDL_Texture* stateTextTexture, SDL_Texture* roundTextTexture)
{
	SDL_DestroyTexture(nameTextTexture);
	SDL_DestroyTexture(scoreTextTexture);
	SDL_DestroyTexture(stateTextTexture);
	SDL_DestroyTexture(roundTextTexture);
}

void logic(int* player, int* random, Cell grid[][3], int gridsum[][2], int gridsumdia[], bool* empty, int scores[], int* gameState)
{
	update_grid(gridsum, gridsumdia, grid, *empty);
	*empty = there_empty(grid);
	*gameState = checkGameState(gridsum, gridsumdia, *empty, scores);
	if (*gameState != InGame)
	{
		resetGrid(gridsum, gridsumdia, grid, empty);
		*random = rand() % 2;
		if (random == 0) *player = O;
		else *player = CROSS;
	}

		

	scoreHandler(scores, *gameState);

	
}