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
    entity->displayed = 1;
    entity->animate = 0;
    return entity;
}

// entity_t            *create_animated_entity(
//     SDL_Renderer    *renderer,
//     char            *name,
//     char            **filenames
// ) {
//     entity_t    *entity;

//     log_warn("create_animated_entity doesn't work for now. DO NOT USE");
//     renderer = NULL;
//     name = NULL;
//     filenames = NULL;
//     return NULL;

//     if(name == NULL)
//         return NULL;

//     entity = _init_entity();
//     entity->name = name;

//     if (add_filenames_to_entity(entity, filenames) == 1)
//     {
//         destroy_entity(entity);
//         return NULL;
//     }

//     entitys_manager(entity);
//     return entity;
// }

entity_t            *create_entity(
    SDL_Renderer    *renderer,
    char            *name,
    char            *filename
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

    if (filename != NULL)
    {
        log_debug("filename for entity : %s", filename);
        if (
            add_filename_to_entity(entity, filename) == 1
            || _create_entity_sprites(renderer, entity) == 1
        )
        {
            log_warn("filename specified but failed to created the sprite, destroying entity");
            destroy_entity(entity);
            return NULL;
        }
    }
    log_debug("entity successfuly created");

    entitys_manager(entity);
    log_debug("created entity '%s' : %p", name, entity);
    return entity;
}

int                 destroy_entity(entity_t *entity)
{
    char            **filename;
    SDL_Texture     **sprite;

    filename = entity->file_names;
    sprite = entity->sprites;
    while(filename != NULL && *filename++)
    {
        SDL_DestroyTexture(*sprite);
        free(filename);
        sprite++;
        filename++;
    }

    free(entity);
    return 0;
}
