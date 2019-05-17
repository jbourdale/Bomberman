/*
** sprite.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "sprite.h"

/**
 * @brief      Create SDL_Texture from a filename
 *
 * @param      renderer  The SDL renderer
 * @param      filename  The filename
 * @param      sprite    The sprite
 *
 * @return     status   Load texture end status
 *              <ul>
 *                  <li>0 = Correctly created</li>
 *                  <li>1 = An error occured</li>
 *              </ul>
 */
int               EGB_SDL_LoadTexture(SDL_Renderer* renderer, char *filename, SDL_Texture **sprite)
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
    //free(rwop);

    *sprite = SDL_CreateTextureFromSurface(renderer, surface);
    return 0;
}
