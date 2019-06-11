/*
** texture.c for  in /Bomberman/bourda_j
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
    EGB_Component_Texture *component, *cpy;
    char *payload;

    component = (EGB_Component_Texture *)*comp;

    cpy = malloc(sizeof(EGB_Component_Texture));
    cpy->name = strdup(component->name);
    cpy->resource_path = strdup(component->resource_path);

    payload = malloc(1000);
    sprintf(payload, "texture_component;%s", strdup(cpy->resource_path));
    return payload;
}

void                        *EGB_Component_TextureUnserializer(char *raw)
{
    char    *token;

    if (raw == NULL) {
        log_debug("no raw data to parse");
        return NULL;
    }
    token = strtok_r(raw, ";", &raw);
    token = strtok_r(NULL, ";", &raw);

    return EGB_Component_CreateTexture(token);
}


int 		EGB_Component_DestroyTexture() {
	return 1;
}
