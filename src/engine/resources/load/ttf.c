/*
** png.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "load.h"

/**
 * @brief      Load a TTF file and create a TTF_Font from it
 *
 * @param      filename  The filename
 * @param      size  	 font size
 *
 * @return     TTF_Font fully initialized or NULL
 */
TTF_Font            *EGB_Resource_LoadTTF(char *filename, int size)
{
    return TTF_OpenFont(filename, size); //this opens a font style and sets a size
}
