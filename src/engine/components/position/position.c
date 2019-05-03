/*
** position.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "position.h"

EGB_Component_Position    *EGB_Component_CreatePosition(int x, int y, int z, int width, int height)
{
    EGB_Component_Position    *component;

    component = malloc(sizeof(EGB_Component_Position));
    component->name = strdup("position_component");
    component->x = x;
    component->y = y;
    component->z = z;
    component->width = width;
    component->height = height;
    return component;
}

int                         EGB_Component_DestroyPosition(EGB_Entity *entity)
{
    EGB_Component_Position    *comp;

    comp = (EGB_Component_Position *)EGB_FindComponentByName(entity, "position_component");
    if (comp == NULL)
        return 1;

    free(comp->name);
    free(comp);
    return 0;
}

int EGB_Component_PositionToRect(EGB_Component_Position *comp, SDL_Rect *rect)
{
    if (rect == NULL || comp == NULL)
        return 1;
    rect->x = comp->x;
    rect->y = comp->y;
    rect->w = comp->width;
    rect->h = comp->height;
    return 0;
}
