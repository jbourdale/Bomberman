/*
** sprite.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "sprite.h"

int               create_sprite(SDL_Renderer* renderer, char *filename, SDL_Texture **sprite)
{
    SDL_RWops     *rwop;
    SDL_Surface   *surface;

    rwop = SDL_RWFromFile(filename, "rb");
    surface = IMG_LoadPNG_RW(rwop);
    if (surface == NULL)
    {
        log_error("[ERROR SDL] Can't create surface (%s)\n", SDL_GetError());
        return 1;
    }
    free(rwop);

    *sprite = SDL_CreateTextureFromSurface(renderer, surface);
    return 0;
}
