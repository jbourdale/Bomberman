/*
** engine.c for  in /home/dev/C/My_FTL/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "engine.h"

int             run()
{
    int         quit;
    SDL_Event   e;

    quit = 0;
    while (quit == 0)
    {
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
        SDL_Delay(20);
    }
    return 0;
}

int start_engine(SDL_Window *window, SDL_Renderer *renderer)
{
    if(init_SDL(window, renderer))
    {
        log_error("Couldn't initialize SDL.");
        return 1;
    }
    return run();
}

int stop_engine(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
