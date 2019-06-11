/*
** textual.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/


#ifndef __COMPONENT_TEXTUAL_H__
#define __COMPONENT_TEXTUAL_H__

#include "../../engine.h"

typedef struct          EGB_Component_Textual_s
{
    char        *name;
    char        *text;
    TTF_Font    *font_resource;
}                       EGB_Component_Textual;

EGB_Component_Textual   *EGB_Component_CreateTextual(char *text, char *font);
int                     EGB_Component_Textual_SetText(EGB_Component_Textual *comp, char *new_text);
char                    *EGB_Component_TextualSerializer(void **comp);
void                    *EGB_Component_TextualUnserializer(char *raw);
int                     EGB_Component_DestroyTextual();

#endif
