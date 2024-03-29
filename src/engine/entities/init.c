/*
** init.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entities.h"


/**
 * @brief      Init an entity
 *
 * @param      name  The entity name
 *
 * @return     entity A pointer on the new created entity
 */
EGB_Entity        *EGB_Entity_Create(char *name)
{
    EGB_Entity    *entity;

    entity = malloc(sizeof(EGB_Entity));
    entity->name = name;
    entity->components = NULL;
    entity->server_side = 0;

    entity->on_destroy = NULL;

    entity->render = EGB_Entity_DefaultRenderer;
    entity->displayed = 1;

    EGB_Manager_Entity(EGB_Manager_Add, entity);
    return entity;
}

EGB_Entity        *EGB_Entity_Copy(EGB_Entity *entity)
{
    EGB_Entity    *entity_copy;

    entity_copy = malloc(sizeof(EGB_Entity));
    entity_copy->name = entity->name;
    entity_copy->components = NULL;
    entity_copy->on_destroy = entity->on_destroy;
    entity_copy->render = entity->render;
    entity_copy->displayed = 1;

    return entity_copy;
}


/**
 * @brief      Entity destructor
 *
 * @param      entity  The entity
 *
 * @return     status   Return 0 if the entity successfuly destroy, overwise return 1
 */
int                 EGB_Entity_Destroy(EGB_Entity *entity)
{
    if (entity == NULL)
        return 1;
    if (entity->name == NULL)
        return 1;

    if (strcmp(entity->name, "fps_indicator") == 0)
        return 1;

    if (entity->on_destroy != NULL)
        entity->on_destroy(entity);

    // Remove entity from managers / observables
    EGB_Manager_Entity(EGB_Manager_Delete, entity);
    EGB_Observable_Position(EGB_Manager_Delete, entity);
    EGB_Observable_Event_KeyStroke(EGB_Manager_Delete, entity);
    EGB_Observable_Event_Click(EGB_Manager_Delete, entity);
    EGB_Observable_Event_Hover(EGB_Manager_Delete, entity);
    EGB_Manager_Collision(EGB_Manager_Delete, entity);
    free(entity);
    return 0;
}
