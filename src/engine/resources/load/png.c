/*
** png.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "load.h"

/**
 * @brief      Load a PNG file and create a SDL_Texture from it
 *
 * @param      filename  The filename
 *
 * @return     SDL_Texture fully initialized or NULL
 */
SDL_Texture         *EGB_Resource_LoadPNG(char *filename)
{
    SDL_Renderer    *renderer;
    SDL_Texture     *texture;

    renderer = EGB_SDL_GetCurrentRenderer();
    texture = NULL;
    if(EGB_SDL_LoadTexture(renderer, filename, &texture)) {
        log_debug("A NULL sprite have been created, aborting.");
        return NULL;
    }
    return texture;
}
