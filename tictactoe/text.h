#pragma once
#include <sstream>
#include <SDL_ttf.h>

void text(SDL_Texture** textTexture,const char* path, TTF_Font* font, SDL_Color color, SDL_Point pos, SDL_Renderer* renderer);