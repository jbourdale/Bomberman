/*
** engine.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "engine.h"

int             framerate_regulation_timer; // Used to regulate fps rate 

int             run_engine(SDL_Renderer *renderer)
{
    int         quit;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    quit = 0;
    while (quit == 0)
    {
        start_framerate_regulation();
        
        quit = handle_events();

        SDL_RenderClear(renderer);
        render_entitys(renderer);
        SDL_RenderPresent(renderer);

        regulate_frame_rate();

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
    create_fps_indicator(*renderer);
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


void                        start_framerate_regulation()
{
    framerate_regulation_timer = SDL_GetTicks();
}

void                        regulate_frame_rate()
{
    entity_t                *entity;
    fpsrate_component_t     *comp;

    entity = find_first_entity_by_name("fps_indicator");
    if (entity == NULL)
        return ;
    comp = (fpsrate_component_t *)find_component_by_name(entity, "fpsrate_component");
    if (comp == NULL)
        return ;

    log_debug("fps rate : %d", comp->fpsrate);

    if ( (SDL_GetTicks() - framerate_regulation_timer) < 1000 / comp->fpsrate ) {
        log_debug("delay : %d", (1000 / comp->fpsrate) - (SDL_GetTicks() - framerate_regulation_timer));
        SDL_Delay((1000 / comp->fpsrate) - (SDL_GetTicks() - framerate_regulation_timer));
    }
    else
        log_debug("delay : 0");

}