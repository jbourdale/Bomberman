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
	SDL_Renderer		*renderer;

	renderer = get_current_renderer();

	comp = malloc(sizeof(texture_component_t));
	comp->name = strdup("texture_component");

	texture = NULL;
    if(create_sprite(renderer, filename, &texture)) {
        log_debug("A NULL sprite have been created, aborting.");
        return NULL;
    }
	comp->texture = texture;
	return comp;
}

int 		destroy_texture_component() {
	return 1;
}