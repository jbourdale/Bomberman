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

  rwop = SDL_RWFromFile(filename, "rb");
  sprite = IMG_LoadPNG_RW(rwop);
  if (sprite == NULL)
    {
      printf("[ERROR SDL] Can't create sprite\n");
      return NULL;
    }
  free(rwop);
  return sprite;
}
