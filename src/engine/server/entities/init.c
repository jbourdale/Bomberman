/*
** init.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entities.h"

/**
 * @brief      Init an entity server side
 *
 * @param      name  The entity name
 *
 * @return     entity A pointer on the new created entity
 */
EGB_Entity        *EGBS_Entity_Create(char *name)
{
    EGB_Entity    *entity;

    entity = malloc(sizeof(EGB_Entity));
    entity->name = name;
    entity->components = NULL;
    entity->server_side = 1;

    entity->on_destroy = NULL;

    entity->render = EGB_Entity_DefaultRenderer;
    entity->displayed = 1;

    EGBS_Manager_Entity(EGB_Manager_Add, entity);
    return entity;
}

int                 EGBS_Entity_Destroy(EGB_Entity *entity)
{
    if (entity == NULL)
        return 1;

    log_debug("EGB_Entity_Destroy : %s", entity->name);

    if (strcmp(entity->name, "fps_indicator") == 0)
        return 1;

    if (entity->on_destroy != NULL)
        entity->on_destroy(entity);

    // Remove entity from manager
    EGBS_Manager_Entity(EGB_Manager_Delete, entity);
    free(entity);
    return 0;
}
