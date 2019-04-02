#ifndef __GUI_H__
#define __GUI_H__

#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/*************************
 *    CONSTANTES         *
 *************************/
#define     GUI_WINDOW_TITLE "Bomberman"

/*************************
 *        INIT.C         *
 *************************/
int         init_SDL(SDL_Window **window, SDL_Renderer **renderer);

/*************************
 *        GUI.C         *
 *************************/
int                 run();

#endif
