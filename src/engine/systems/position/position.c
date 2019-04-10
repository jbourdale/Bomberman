/*
** position.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "../../engine.h"
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

void    move_position_component_right(position_component_t *comp, int offset)
{
    if (comp == NULL)
        return;
    comp->x += offset;
}

void    move_position_component_left(position_component_t *comp, int offset)
{
    if (comp == NULL)
        return;
    comp->x -= offset;
}

void    move_position_component_up(position_component_t *comp, int offset)
{
    if (comp == NULL)
        return;
    comp->y -= offset;

}

void    move_position_component_down(position_component_t *comp, int offset)
{
    if (comp == NULL)
        return;
    comp->y += offset;
}
