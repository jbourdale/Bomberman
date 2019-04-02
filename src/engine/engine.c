/*
** engine.c for  in /home/dev/C/My_FTL/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "engine.h"

int start_engine(SDL_Window **window, SDL_Renderer **renderer)
{
    if(init_SDL(window, renderer))
    {
        log_error("Couldn't initialize SDL.");
        return 1;
    }
    return 0;
}

int init_SDL(SDL_Window **window, SDL_Renderer **renderer)
{
    *renderer = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return 1;
    else
    {
        if (!TTF_Init())
        {
            *window = NULL;
            *window = SDL_CreateWindow(
                "title",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                800,
                600,
                SDL_WINDOW_SHOWN
            );
            if (*window != NULL)
                *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
            else
                return 1;
        }
        else
            return 1;
    }
    return 0;
}
