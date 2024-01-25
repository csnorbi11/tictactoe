#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window* g_Window;
extern SDL_Texture* g_Texture;
extern SDL_Renderer* g_Renderer;

extern TTF_Font* g_Font;

bool init_game();
void free();
SDL_Texture* loadImg(std::string path, SDL_Renderer* renderer);