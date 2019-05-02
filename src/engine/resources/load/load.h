/*
** load.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __LOAD_H__
#define __LOAD_H__

#include "../../engine.h"

#define EGB_DEFAULT_FONT_SIZE 15

SDL_Texture *EGB_load_png_resource(char *filename);
TTF_Font    *EGB_load_ttf_resource(char *filename, int size);
int         EGB_load_resources();
int         EGB_load_resource(char* resource_path);
char        *EGB_get_filename_ext(char *filename);
char        *EGB_str_remove_substr(char *str, const char *sub);

#endif
