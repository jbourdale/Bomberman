/*
** events.c for  in /home/dev/C/My_FTL/bourda_j
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
        else if (e.type == SDL_KEYDOWN) {
            log_debug("Key stroke");
            handle_entity_key_events(e);
        }

    }

    return 0;
}

int                         handle_entitys_click(SDL_Event e)
{
    entity_t                **entitys;
    SDL_Rect                entity_rect;
    SDL_Point               clic;
    position_component_t    *comp;
    int                     i;

    clic.x = e.button.x;
    clic.y = e.button.y;

    entitys = entitys_manager(NULL);
    i = 0;
    while(entitys[i] != NULL)
    {
        log_debug("handling entity %s", entitys[i]->name);

        comp = (position_component_t *)find_component_by_name(entitys[i], "position_component");
        log_debug("comp founded : (%d,%d,%d,%d)", comp->x, comp->y, comp->width, comp->height);

        position_component_to_rect(comp, &entity_rect);
        log_debug("rect: (%d,%d,%d,%d)", entity_rect.x, entity_rect.y, entity_rect.w, entity_rect.h);

        if (entitys[i]->on_click != NULL && SDL_PointInRect(&clic, &entity_rect) == SDL_TRUE)
            entitys[i]->on_click(entitys[i], e);
        i++;
    }
    return 0;
}


int             handle_entity_key_events(SDL_Event e)
{
    entity_t    **entitys;
    int         i;

    entitys = entitys_manager(NULL);
    i = 0;
    while(entitys[i] != NULL)
    {
        if(entitys[i]->on_key_stroke != NULL)
        {
            entitys[i]->on_key_stroke(entitys[i], e);
        }
        i++;
    }
    return 0;
}
