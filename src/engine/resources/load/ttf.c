/*
** png.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "load.h"

TTF_Font            *EGB_Resource_LoadTTF(char *filename, int size)
{
    return TTF_OpenFont(filename, size); //this opens a font style and sets a size
}
