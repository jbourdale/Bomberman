/*
** init.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entitys.h"

entity_t        *create_entity(
    char        *name
)
{
    log_debug("create_entity");
    entity_t    *entity;

    entity = malloc(sizeof(entity_t));
    entity->name = name;
    entity->components = NULL;

    entity->on_init = NULL;
    entity->on_key_stroke = NULL;
    entity->on_click = NULL;
    entity->on_destroy = NULL;
    
    entity->render = _base_entity_render;
    entity->displayed = 1;

    entitys_manager(entity);
    return entity;
}

int                 destroy_entity(entity_t *entity)
{
    free(entity);
    return 0;
}
