/*
** png.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "load.h"

SDL_Texture         *EGB_load_png_resource(char *filename)
{
    SDL_Renderer    *renderer;
    SDL_Texture     *texture;

    renderer = get_current_renderer();
    texture = NULL;
    if(create_sprite(renderer, filename, &texture)) {
        log_debug("A NULL sprite have been created, aborting.");
        return NULL;
    }
    return texture;
}
