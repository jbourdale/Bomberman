#ifndef __SDL_H__
#define __SDL_H__

#include "../engine.h"
#include "sprite/sprite.h"

#define GUI_WINDOW_TITLE "Bomberman"
#define LOGICAL_WINDOW_WIDTH 1920
#define LOGICAL_WINDOW_HEIGHT 1080

int init_SDL(SDL_Window *window, SDL_Renderer *renderer);
int init_window(SDL_Window **window);

#endif
