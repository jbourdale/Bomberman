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

typedef struct 		texture_component_s
{
	char 			*name;
	SDL_Texture 	*texture;
}					texture_component_t;

texture_component_t 	*EGB_Component_CreateTexture(char *filename);
int 					EGB_Component_DestroyTexture();

#endif