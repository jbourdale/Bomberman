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

    //free(comp->name);
    //free(comp);
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

EGB_Entity *EGB_FindEntityByPosition(int x, int y, int z) {
    EGB_Entity                  *entity;
    EGB_Entity_Manager          *entities_manager;
    EGB_Entity_Manager_Element  *manager_iterator;
    EGB_Component_Position      *position_comp;

    log_debug("EGB_FindEntityByPosition");

    entities_manager = EGB_Observable_Position(EGB_Manager_Retrieve);
    if (entities_manager == NULL)
        return NULL;
    manager_iterator = entities_manager->first;
    while (manager_iterator != NULL)
    {
        entity = manager_iterator->entity;
        position_comp = EGB_FindComponentByName(
            entity,
            "position_component"
        );
        if (position_comp->x == x
            && position_comp->y == y
            && position_comp->z == z)
            return entity;
        manager_iterator = manager_iterator->next;
    }
    return NULL;
}
