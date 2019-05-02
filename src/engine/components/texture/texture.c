/*
** sprite.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "texture.h"

texture_component_t 	*EGB_Component_CreateTexture(char *filename)
{
	texture_component_t *comp;
	SDL_Texture 		*texture;

	comp = malloc(sizeof(texture_component_t));
	comp->name = strdup("texture_component");

	texture = NULL;
    if((texture = (SDL_Texture *)EGB_Get_Resource(filename)) == NULL) {
        log_debug("Can't find %s resource", filename);
        return NULL;
    }
	comp->texture = texture;
	return comp;
}

int 		EGB_Component_DestroyTexture() {
	return 1;
}