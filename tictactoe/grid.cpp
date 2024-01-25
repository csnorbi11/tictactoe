#include "grid.h"
#include "window.h"

int grid_dimension;
SDL_Point gridPos;
SDL_Rect gridRect;

float lineWidth;
float cellDimension;
float cellOffSet;

//init grid dimension, positions and status
void init_grid(Cell grid[][3])
{
	grid_dimension = SCREEN_HEIGHT * 0.667;
	cellDimension = grid_dimension * 0.334;
	cellOffSet = cellDimension * 0.1;
	lineWidth = grid_dimension * 0.02;
	gridPos = {
		(int)(SCREEN_WIDTH * 0.5) - (int)(grid_dimension * 0.5),
		(int)(SCREEN_HEIGHT * 0.3)
	};
	gridRect = {
		gridPos.x,
		gridPos.y,
		grid_dimension,
		grid_dimension
	};

	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			grid[y][x].status = EMPTY;
			if (x==0)
			{
				grid[y][x].startPos.x = gridPos.x + (x * cellDimension);
				grid[y][x].startPos.y = gridPos.y + (y * cellDimension);
			}
			else
			{
				grid[y][x].startPos.x = gridPos.x + (x * cellDimension) + lineWidth;
				grid[y][x].startPos.y = gridPos.y + (y * cellDimension) + lineWidth;
			}
			
			grid[y][x].endPos.x = grid[y][x].startPos.x + cellDimension;
			grid[y][x].endPos.y = grid[y][x].startPos.y + cellDimension;
		}
	}
}
//render grid
void render_grid(Cell grid[][3], SDL_Texture* gridImg, SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, gridImg, NULL, &gridRect);
}
//check if there is any cells which are empty
bool there_empty(Cell grid[][3])
{
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			if (grid[y][x].status == EMPTY)
				return true;
		}
	}
	return false;
}
//render cells by their status
void render_cells(Cell grid[][3], SDL_Texture* xTexture, SDL_Texture* oTexture, SDL_Texture* cellTexture[][3], SDL_Renderer* renderer)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			SDL_Rect cellRect = { gridPos.x + cellOffSet+cellDimension*x,gridPos.y + cellOffSet + cellDimension * y,cellDimension - cellOffSet * 2,cellDimension - cellOffSet * 2};
			if (grid[y][x].status == O)
			{
				SDL_RenderCopy(renderer, oTexture, NULL, &cellRect);
			}
			else if (grid[y][x].status == CROSS)
			{
				SDL_RenderCopy(renderer, xTexture, NULL, &cellRect);
			}
		}
	}
}
//sums up every row, cols and dia to check if any player win
void update_grid(int gridsum[][2], int gridsumdia[], Cell grid[][3], bool empty)
{
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			gridsum[y][x] = 0;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int x = 0; x < 3; x++)
		{
			gridsum[i][0] += grid[i][x].status;
			gridsum[i][1] += grid[x][i].status;
		}

	}
	
	gridsumdia[0] = grid[0][0].status + grid[1][1].status + grid[2][2].status;
	gridsumdia[1] = grid[0][2].status + grid[1][1].status + grid[2][0].status;

	empty = there_empty(grid);
}


//old grid renderer when the grid rendered by sdl rects
/*
void render_grid(Cell grid[][3], SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
	SDL_RenderFillRect(renderer, &gridRect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
	SDL_Rect verticalLine = { gridPos.x + grid_dimension * 0.334,gridPos.y,lineWidth,grid_dimension };
	SDL_RenderFillRect(renderer, &verticalLine);
	verticalLine.x = gridPos.x + grid_dimension * 0.667;
	SDL_RenderFillRect(renderer, &verticalLine);
	SDL_Rect horizontalLine = { gridPos.x,gridPos.y + grid_dimension * 0.334,grid_dimension,lineWidth };
	SDL_RenderFillRect(renderer, &horizontalLine);
	horizontalLine.y = gridPos.y + grid_dimension * 0.667;
	SDL_RenderFillRect(renderer, &horizontalLine);
}*/
//old cell renderer when cells are rendered by sdl lines
/*
void render_cells(Cell grid[][3], SDL_Renderer* renderer)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (grid[y][x].status == O)
			{
				SDL_RenderDrawLine(renderer, grid[y][x].endPos.x-(cellDimension/2),
					grid[y][x].startPos.y,
					grid[y][x].endPos.x - (cellDimension / 2),
					grid[y][x].endPos.y);
			}
			else if (grid[y][x].status == CROSS)
			{
				SDL_RenderDrawLine(renderer, grid[y][x].startPos.x,
					grid[y][x].endPos.y-(cellDimension/2),
					grid[y][x].endPos.x,
					grid[y][x].endPos.y-(cellDimension/2));
			}
		}
	}
}
*/