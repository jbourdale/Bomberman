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
