/*
** position.c for  in /home/dev/C/My_FTL/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "position.h"

position_component_t    *create_position_component(int x, int y, int width, int height)
{
    position_component_t    *component;

    component = malloc(sizeof(position_component_t));
    component->name = strdup("position_component");
    component->x = x;
    component->y = y;
    component->width = width;
    component->height = height;
    return component;
}

int                         destroy_position_component(entity_t *entity)
{
    position_component_t    *comp;

    comp = (position_component_t *)find_component_by_name(entity, "position_component");
    if (comp == NULL)
        return 1;

    free(comp->name);
    free(comp);
    return 0;
}

int position_component_to_rect(position_component_t *comp, SDL_Rect *rect)
{
    log_debug("position_component_to_rect");
    rect->x = comp->x;
    rect->y = comp->y;
    rect->w = comp->width;
    rect->h = comp->height;
    log_debug("end");
    return 0;
}