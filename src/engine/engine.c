/*
** engine.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "engine.h"

int             framerate_regulation_timer; // Used to regulate fps rate 

int                 run_engine()
{
    int             quit;
    SDL_Renderer    *renderer;

    renderer = get_current_renderer();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    quit = 0;
    while (quit == 0)
    {
        start_framerate_regulation();
        
        quit = handle_events();
        log_debug("handle_events end");
        SDL_RenderClear(renderer);
        render_entitys();
        SDL_RenderPresent(renderer);

        regulate_frame_rate();

    }
    return 0;
}

int start_engine()
{
    log_debug("start_engine");
    if(init_SDL())
    {
        log_error("Couldn't initialize SDL.");
        return 1;
    }
    create_fps_indicator();
    return 0;
}

int stop_engine()
{
    SDL_DestroyRenderer(get_current_renderer());
    SDL_DestroyWindow(SDL_GL_GetCurrentWindow());
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

    if ( (SDL_GetTicks() - framerate_regulation_timer) < 1000 / comp->fpsrate ) {
        SDL_Delay((1000 / comp->fpsrate) - (SDL_GetTicks() - framerate_regulation_timer));
    }
}