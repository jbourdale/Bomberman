/*
** sprite.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "texture.h"

EGB_Component_Texture 	*EGB_Component_CreateTexture(char *filename)
{
	EGB_Component_Texture *comp;
	SDL_Texture 		*texture;

	comp = malloc(sizeof(EGB_Component_Texture));
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