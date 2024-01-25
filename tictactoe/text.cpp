#include "text.h"

//render text
void text(SDL_Texture** textTexture, const char* path, TTF_Font* font, SDL_Color color, SDL_Point pos, SDL_Renderer* renderer)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, path, color);

	*textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_Rect textQuad = { pos.x- textSurface->w/2,pos.y,textSurface->w,textSurface->h };

	SDL_RenderCopy(renderer, *textTexture, NULL, &textQuad);

	SDL_FreeSurface(textSurface);
}