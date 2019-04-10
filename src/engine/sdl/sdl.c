/*
** engine.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "sdl.h"

int init_SDL(SDL_Window **window, SDL_Renderer **renderer)
{
    *renderer = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return 1;
    else
    {
        if (!TTF_Init())
        {
            if (init_window(window) != 0 || *window == NULL)
                return 1;
            *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
            SDL_RenderSetLogicalSize(*renderer, LOGICAL_WINDOW_WIDTH, LOGICAL_WINDOW_HEIGHT);
        }
        else
            return 1;
    }
    return 0;
}

int                     init_window(SDL_Window **window)
{
    SDL_DisplayMode     mode;
    if (SDL_GetCurrentDisplayMode(0, &mode))
        return 1;

    *window = NULL;
    *window = SDL_CreateWindow(
        GUI_WINDOW_TITLE,
        0,
        0,
        mode.w,
        mode.h,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS
    );
    return 0;
}
