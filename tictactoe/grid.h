#pragma once
#include "window.h"
#include <stdbool.h>

enum {
	CROSS=2,
	O=5,
	EMPTY=0
};

typedef struct Cell {
	SDL_Point startPos;
	SDL_Point endPos;
	int status;
} Cell;

void init_grid(Cell grid[][3]);
void render_grid(Cell grid[][3], SDL_Texture* gridImg, SDL_Renderer* renderer);
bool there_empty(Cell grid[][3]);
void render_cells(Cell grid[][3], SDL_Texture* xTexture, SDL_Texture* oTexture, SDL_Texture* cellTexture[][3], SDL_Renderer* renderer);
void update_grid(int gridsum[][2], int gridsumdia[], Cell grid[][3], bool empty);