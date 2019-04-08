/*
** engine.c for  in /home/dev/C/My_FTL/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "engine.h"

int             run_engine(SDL_Renderer *renderer)
{
    int         quit;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    quit = 0;
    while (quit == 0)
    {
        quit = handle_events();

        SDL_RenderClear(renderer);
        render_entitys(renderer);
        SDL_RenderPresent(renderer);
        // SDL_Delay(10);
    }
    return 0;
}

int start_engine(SDL_Window **window, SDL_Renderer **renderer)
{
    if(init_SDL(window, renderer))
    {
        log_error("Couldn't initialize SDL.");
        return 1;
    }
    printf("renderer addr in start_engine : %p \n", *renderer);
    return 0;
}

int stop_engine(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
