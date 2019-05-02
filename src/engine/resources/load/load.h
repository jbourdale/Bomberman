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

void 		EGB_Iterate_RootResourcesDir(const char *dirname);
SDL_Texture *EGB_Resource_LoadPNG(char *filename);
TTF_Font    *EGB_Resource_LoadTTF(char *filename, int size);
int         EGB_LoadResources();
int         EGB_LoadResource(char* resource_path);
char        *EGB_Get_FilenameExt(char *filename);
char        *EGB_Str_Remove_Substr(char *str, const char *sub);

#endif
