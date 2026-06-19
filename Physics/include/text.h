#ifndef TEXT_H
#define TEXT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

bool Text_Init(void);
void Text_Shutdown(void);
void Text_Draw(SDL_Renderer *renderer, const char *text, int x, int y);

#endif