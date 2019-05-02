/*
** sdl.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __SDL_H__
#define __SDL_H__

#include "../engine.h"
#include "sprite/sprite.h"

#define GUI_WINDOW_TITLE "Bomberman"
#define LOGICAL_WINDOW_WIDTH 1920
#define LOGICAL_WINDOW_HEIGHT 1080

int 			EGB_SDL_Init();
SDL_Renderer 	*EGB_SDL_GetCurrentRenderer();
int 			EGB_SDL_InitWindow(SDL_Window **window);

#endif
