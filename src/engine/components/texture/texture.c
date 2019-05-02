/*
** sprite.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "texture.h"

texture_component_t 	*create_texture_component(char *filename)
{
	texture_component_t *comp;
	SDL_Texture 		*texture;

	comp = malloc(sizeof(texture_component_t));
	comp->name = strdup("texture_component");

	texture = NULL;
    if((texture = (SDL_Texture *)EGB_get_resource(filename)) == NULL) {
        log_debug("Can't find %s resource", filename);
        return NULL;
    }
	comp->texture = texture;
	return comp;
}

int 		destroy_texture_component() {
	return 1;
}