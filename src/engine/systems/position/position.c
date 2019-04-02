/*
** position.c for  in /home/dev/C/My_FTL/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "position.h"

entity_t                    *set_entity_position(entity_t *entity, int x, int y)
{
    position_component_t    *comp;

    comp = (position_component_t *)find_component_by_name(entity, "position_component");
    comp->x = x;
    comp->y = y;
    return entity;
}

entity_t                    *set_entity_dimensions(entity_t *entity, int w, int h)
{
    position_component_t    *comp;

    comp = (position_component_t *)find_component_by_name(entity, "position_component");

    comp->width = w;
    comp->height = h;
    return entity;
}
