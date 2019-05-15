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
    comp->resource_path = strdup(filename);

	texture = NULL;
    if((texture = (SDL_Texture *)EGB_Get_Resource(filename)) == NULL) {
        log_debug("Can't find %s resource", filename);
        return NULL;
    }
	comp->texture = texture;
	return comp;
}

char    *EGB_Component_TextureSerializer(void **comp)
{
    EGB_Component_Texture *component;
    char *payload;

    log_debug("EGB_Component_TextureSerializer");

    payload = malloc(1000);
    component = (EGB_Component_Texture *)*comp;
    sprintf(payload, "texture_component;%s", strdup(component->resource_path));
    return payload;
}


int 		EGB_Component_DestroyTexture() {
	return 1;
}
