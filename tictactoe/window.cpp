#include "window.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* g_Window = NULL;
SDL_Texture* g_Texture = NULL;
SDL_Renderer* g_Renderer = NULL;

TTF_Font* g_Font = NULL;

//init sdl, sdl_image, window, renderer, sdl_ttf
bool init_game()
{
	bool exit = false;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("Cannot init SDL: %s", SDL_GetError());
		return exit = true;
	}
	if (IMG_Init(IMG_INIT_PNG) < 0)
	{
		SDL_Log("Cannot init SDL image: %s", IMG_GetError());
		return exit = true;
	}
	g_Window = SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (g_Window == NULL)
	{
		SDL_Log("Cannot create the window: %s", SDL_GetError());
		return exit = true;
	}
	g_Renderer = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED);
	if (g_Renderer == NULL)
	{
		SDL_Log("Cannot create the renderer: %s", SDL_GetError());
		return exit = true;
	}
	if (TTF_Init() == -1)
	{
		SDL_Log("Cannot init TTF lib: %s", TTF_GetError());
		return exit = true;
	}
	g_Font = TTF_OpenFont("8bitOperatorPlus8-Regular.ttf", 64);
	if (g_Font == NULL)
	{
		SDL_Log("Cannot load the font: %s", TTF_GetError());
		return exit = true;
	}


	return exit;
}
//free up renderer, window and quit
void free()
{
	SDL_DestroyRenderer(g_Renderer);
	g_Renderer = NULL;

	SDL_DestroyWindow(g_Window);
	g_Window = NULL;

	SDL_Quit();
}
//load images into texture
SDL_Texture* loadImg(std::string path, SDL_Renderer* renderer)
{
	SDL_Surface* surfaceToLoad = IMG_Load(path.c_str());
	if (surfaceToLoad == NULL)
	{
		SDL_Log("Cannot load the img to surface: %s\n(%s)", SDL_GetError(), path.c_str());
		return NULL;
	}
	SDL_Texture* textureToLoadInto = SDL_CreateTextureFromSurface(renderer, surfaceToLoad);
	if (textureToLoadInto == NULL)
	{
		SDL_Log("Cannot create texture from surface: %s\n(%s)", SDL_GetError(), path.c_str());
		return NULL;
	}
	SDL_FreeSurface(surfaceToLoad);

	return textureToLoadInto;
}