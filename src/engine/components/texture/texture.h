/*
** sprite.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "../../engine.h"

typedef struct 		EGB_Component_Texture_s
{
	char 			*name;
    char            *resource_path;
	SDL_Texture 	*texture;
}					EGB_Component_Texture;

EGB_Component_Texture 	*EGB_Component_CreateTexture(char *filename);
char                    *EGB_Component_TextureSerializer(void *comp);
int 					EGB_Component_DestroyTexture();

#endif
