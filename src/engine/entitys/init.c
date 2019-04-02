/*
** init.c for  in /home/dev/C/My_FTL/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entitys.h"

entity_t        *_init_entity()
{
    log_debug("_init_entity");
    entity_t    *entity;

    entity = malloc(sizeof(entity_t));
    entity->sprites = NULL;
    entity->file_names = NULL;
    entity->components = NULL;
    entity->on_init = NULL;
    entity->on_click = NULL;
    entity->on_destroy = NULL;
    entity->render = _base_entity_render;
    return entity;
}

entity_t        *create_animated_entity(
    char        *name,
    char        **filenames
) {
    entity_t    *entity;

    if(name == NULL)
        return NULL;

    entity = _init_entity();
    entity->name = name;

    if (add_filenames_to_entity(entity, filenames) == 1)
    {
        destroy_entity(entity);
        return NULL;
    }

    return entity;
}

entity_t        *create_entity(
    char        *name,
    char        *filename
) {
    log_debug("create_entity");
    entity_t    *entity;

    if(name == NULL)
    {
        log_warn("no name specified, aborting entity creation");
        return NULL;
    }

    entity = _init_entity();
    entity->name = name;

    if (filename != NULL && add_filename_to_entity(entity, filename) == 1)
    {
        log_warn("filename specified but failed to created the sprite, destroying entity");
        destroy_entity(entity);
        return NULL;
    }

    log_debug("entity successfuly created");
    return entity;
}

int                 destroy_entity(entity_t *entity)
{
    char            **filename;
    SDL_Surface     **sprite;

    free(entity->name);
    filename = entity->file_names;
    sprite = entity->sprites;
    while(*filename++)
    {
        SDL_FreeSurface(*sprite);
        free(filename);
        sprite++;
        filename++;
    }

    return 0;
}
