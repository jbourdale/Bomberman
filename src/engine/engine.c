/*
** engine.c for  in /home/dev/C/My_FTL/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "engine.h"

int             run(SDL_Renderer *renderer)
{
    int         quit;
    SDL_Event   e;
    position_component_t *pos_comp;

    entity_t *entity = create_entity(renderer, "mario", "./resources/mario.png");
    pos_comp = create_position_component(0, 0, 200, 200);
    add_component_to_entity(entity, (void *)pos_comp);

    log_debug("sprites[0] is NULL ? %d", entity->sprites[0] == NULL);
    log_debug("sprites[0] : %p", entity->sprites[0]);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    quit = 0;
    while (quit == 0)
    {
        SDL_RenderClear(renderer);
        render_entitys(renderer);
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
    return 0;
}

int start_engine(SDL_Window **window, SDL_Renderer **renderer, int flag)
{
    if(init_SDL(window, renderer))
    {
        log_error("Couldn't initialize SDL.");
        return 1;
    }
    printf("renderer addr in start_engine : %p \n", *renderer);
    if (flag == ENGINE_NO_RUN)
        return 0;
    return run(*renderer);
}

int stop_engine(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
