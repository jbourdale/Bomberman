/*
** sprites.c for  in /home/dev/C/My_FTL/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entitys.h"

int             _create_entity_sprite(entity_t *entity, char *filename)
{
    SDL_Surface *sprite;
    SDL_Surface **entity_sprite;
    int         nb_sprite;
    int         new_size;

    sprite = create_sprite(filename);
    if(sprite == NULL)
        return 1;

    entity_sprite = entity->sprites;
    nb_sprite = 0;
    while(*entity_sprite++)
    {
        nb_sprite++;
    }

    new_size = (nb_sprite + 1) * sizeof(SDL_Surface*);
    entity->sprites = realloc(entity->sprites, new_size);
    entity->sprites[nb_sprite + 1] = sprite;
    return 0;
}

int         _create_entity_sprites(entity_t *entity)
{
    char    **filename;

    filename = entity->file_names;
    while(*filename++)
    {
        if(_create_entity_sprite(entity, *filename) == 1)
        {
            destroy_entity(entity);
            return 1;
        }
        filename++;
    }
    return 0;
}
