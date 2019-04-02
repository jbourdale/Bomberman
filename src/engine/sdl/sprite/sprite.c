/*
** sprite.c for  in /home/dev/C/My_FTL/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "sprite.h"

SDL_Surface     *create_sprite(char *filename)
{
    SDL_RWops     *rwop;
    SDL_Surface   *sprite;

    log_debug("create_sprite for filename : %s", filename);
    rwop = SDL_RWFromFile(filename, "rb");
    log_debug("rwop == NULL : %d", rwop == NULL);

    sprite = IMG_LoadPNG_RW(rwop);
    if (sprite == NULL)
    {
        printf("[ERROR SDL] Can't create sprite\n");
        return NULL;
    }
    free(rwop);
    log_debug("returning new sprite");
    return sprite;
}
