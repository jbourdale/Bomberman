/*
** init.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entities.h"

EGB_Entity        *EGB_Entity_Create(char *name)
{
    log_debug("create_entity");
    EGB_Entity    *entity;

    entity = malloc(sizeof(EGB_Entity));
    entity->name = name;
    entity->components = NULL;

    entity->on_destroy = NULL;
    
    entity->render = EGB_Entity_DefaultRenderer;
    entity->displayed = 1;

    log_debug("entity created : %p", entity);
    EGB_Observable_Entity(EGB_Manager_Add, entity);
    return entity;
}

int                 EGB_Entity_Destroy(EGB_Entity *entity)
{
    free(entity);
    return 0;
}
