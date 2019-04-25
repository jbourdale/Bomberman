/*
** events.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "events.h"

int 			handle_events()
{
	SDL_Event 	e;

	if (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) {
            return -1;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
        	log_debug("Click on %d, %d", e.button.x, e.button.y);
            handle_entitys_click(e);
        }
        else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            log_debug("Key stroke");
            handle_entity_key_events(e);
        }
    }

    return 0;
}

int                         handle_entitys_click(SDL_Event e)
{
    SDL_Renderer            *renderer;
    entity_t                **entitys;
    SDL_Rect                entity_rect;
    SDL_Point               clic;
    position_component_t    *comp;
    int                     i, nb_entity;

    renderer = get_current_renderer();
    clic.x = e.button.x;
    clic.y = e.button.y;

    entitys = entitys_manager(NULL);
    nb_entity = 0;
    while(entitys[nb_entity] != NULL)
        nb_entity++;
    i = 0;
    while(i < nb_entity && entitys[i] != NULL)
    {
        log_debug("handling entity %s", entitys[i]->name);

        comp = (position_component_t *)find_component_by_name(entitys[i], "position_component");
        position_component_to_rect(comp, &entity_rect);

        if (entitys[i]->on_click != NULL && SDL_PointInRect(&clic, &entity_rect) == SDL_TRUE)
            entitys[i]->on_click(renderer, entitys[i], e);
        i++;
    }
    return 0;
}


int             handle_entity_key_events(SDL_Event e)
{
    entity_t    **entitys;
    int         i, nb_entity, j;
    entitys = entitys_manager(NULL);
    nb_entity = 0;
    while(entitys[nb_entity] != NULL)
        nb_entity++;

    i = 0;
    j = 0;

    while(i < nb_entity && entitys[i] != NULL)
    {
        entitys = entitys_manager(NULL);
        log_debug("i : %d", i);
        log_debug("entitys[%d] : %p", i, entitys[i]);
        log_debug("entitys[%d]->name : %s", i, entitys[i]->name);
        if(entitys[i]->on_key_stroke != NULL)
        {
            // arr[j] = i;
            // log_debug("j : %d, arr[%d] : %d", j, arr[j], i);
            // j++;
            entitys[i]->on_key_stroke(entitys[i], e);
            log_debug("on_key_stroke end");
        }
        log_debug("entitys[%d] : %p", i, entitys[i]);
        log_debug("entitys addr : %p ", entitys);
        i++;
    }

    // log_debug("youhou");
    // for (int k = j - 1; k >= 0; k--) {
    //     log_debug("arr[%d] : %d", k, arr[k]);
    //     entitys[arr[k]]->on_key_stroke(entitys[arr[k]], e);
    // }

    log_debug("end handle_entity_key_events");
    return 0;
}
