/*
** entity.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entitys.h"

void                        _base_entity_render(SDL_Renderer *renderer, entity_t *entity)
{
    SDL_Rect                screen_position;
    position_component_t    *pos_comp;

    if (!entity->displayed || entity->sprites[0] == NULL)
        return ;
    pos_comp = (position_component_t*)find_component_by_name(entity, "position_component");
    if (pos_comp == NULL)
        return ;

    position_component_to_rect(pos_comp, &screen_position);

    if (entity->animate == 1 &&
        SDL_GetTicks() - entity->last_animation_tick > entity->animation_delai_frame
    )
    {
        entity->last_animation_tick = SDL_GetTicks();
        entity->current_frame++;
        if (entity->sprites[entity->current_frame] == NULL)
            entity->current_frame = 0;
    }

    SDL_RenderCopy(renderer, entity->sprites[entity->current_frame], NULL, &screen_position);
}


void            render_entitys(SDL_Renderer *renderer)
{
    entity_t    **current_entitys;
    int         i;

    // log_debug("render_entitys");
    current_entitys = entitys_manager(NULL);
    // log_debug("current_entitys[0] : %p", current_entitys[0]);
    // log_debug("current_entitys[0] == NULL : %d", current_entitys[0] == NULL);

    i = 0;
    while (current_entitys[i] != NULL)
    {
        // log_debug("loop for entity : %p", current_entitys[i]);
        current_entitys[i]->render(renderer, current_entitys[i]);
        i++;
    }
}
