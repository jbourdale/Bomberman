/*
** position.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "position.h"

position_component_t    *EGB_Component_CreatePosition(int x, int y, int z, int width, int height)
{
    position_component_t    *component;

    component = malloc(sizeof(position_component_t));
    component->name = strdup("position_component");
    component->x = x;
    component->y = y;
    component->z = z;
    component->width = width;
    component->height = height;
    return component;
}

int                         EGB_Component_DestroyPosition(entity_t *entity)
{
    position_component_t    *comp;

    comp = (position_component_t *)EGB_FindComponentByName(entity, "position_component");
    if (comp == NULL)
        return 1;

    free(comp->name);
    free(comp);
    return 0;
}

int EGB_Component_PositionToRect(position_component_t *comp, SDL_Rect *rect)
{
    if (rect == NULL || comp == NULL)
        return 1;
    rect->x = comp->x;
    rect->y = comp->y;
    rect->w = comp->width;
    rect->h = comp->height;
    return 0;
}
