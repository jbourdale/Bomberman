/*
** entity.c for  in /home/dev/C/My_FTL/bourda_j
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

    log_debug("render entity %s", entity->name);
    log_debug("renderer : %p", renderer);

    if (!entity->displayed) {
        log_debug("entity not displayed");
        return ;
    }
    if (entity->sprites[0] == NULL) {
        log_debug("entity have no sprite");
        return ;
    }
    pos_comp = (position_component_t*)find_component_by_name(entity, "position_component");
    if (pos_comp == NULL) {
        log_debug("entity have no position component");
        return ;
    }

    screen_position.x = pos_comp->x;
    screen_position.y = pos_comp->y;
    screen_position.w = pos_comp->width;
    screen_position.h = pos_comp->height;
    log_debug("render sprite : %p", entity->sprites[0]);
    log_debug("at %d,%d,%d,%d", screen_position.x, screen_position.y, screen_position.w, screen_position.h);
    SDL_RenderCopy(renderer, entity->sprites[0], NULL, &screen_position);
}


void            render_entitys(SDL_Renderer *renderer)
{
    entity_t    **current_entitys;
    int         i;

    log_debug("render_entitys");
    current_entitys = entitys_manager(NULL);
    log_debug("current_entitys[0] : %p", current_entitys[0]);
    log_debug("current_entitys[0] == NULL : %d", current_entitys[0] == NULL);

    i = 0;
    while (current_entitys[i] != NULL)
    {
        log_debug("loop for entity : %p", current_entitys[i]);
        current_entitys[i]->render(renderer, current_entitys[i]);
        i++;
    }
}
