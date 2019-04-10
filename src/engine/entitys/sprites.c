/*
** sprites.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entitys.h"

int             _create_entity_sprite(SDL_Renderer *renderer, entity_t *entity, char *filename)
{
    SDL_Texture *sprite;
    SDL_Texture **entity_sprite;
    int         nb_sprite;
    int         new_size;

    log_debug("_create_entity_sprite");

    sprite = NULL;
    if(create_sprite(renderer, filename, &sprite)) {
        log_debug("A NULL sprite have been created, aborting.");
        return 1;
    }
    log_debug("sprite in _create_entity_sprite : %p", sprite);

    entity_sprite = entity->sprites;
    nb_sprite = 0;
    while(entity_sprite != NULL && *entity_sprite++)
    {
        nb_sprite++;
    }

    new_size = (nb_sprite + 2) * sizeof(SDL_Surface*);
    entity->sprites = realloc(entity->sprites, new_size);
    entity->sprites[nb_sprite] = sprite;
    entity->sprites[nb_sprite + 1] = NULL;
    log_debug("entity->sprites[nb_sprite] : %p", entity->sprites[nb_sprite + 1]);
    return 0;
}

int         _create_entity_sprites(SDL_Renderer *renderer, entity_t *entity)
{
    char    **tmp_filename;
    int     nb_filename;
    int     i;

    log_debug("_create_entity_sprites");

    tmp_filename = entity->file_names;
    nb_filename = 0;
    while (tmp_filename != NULL && *tmp_filename++)
        nb_filename++;

    i = 0;
    while(i < nb_filename)
    {
        log_debug("for filename : %s", entity->file_names[i]);
        if(_create_entity_sprite(renderer, entity, entity->file_names[i]) == 1)
        {
            log_debug("went wrong");
            destroy_entity(entity);
            return 1;
        }
        i++;
    }
    log_debug("sprites successfuly created");
    return 0;
}
