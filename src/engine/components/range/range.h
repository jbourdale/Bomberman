/*
** range.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __COMPONENT_RANGE_H__
#define __COMPONENT_RANGE_H__

#include "../../engine.h"

typedef struct          EGB_Component_Range_s
{
    char        *name;
    int         range;
}                       EGB_Component_Range;

EGB_Component_Range 	*EGB_Component_CreateRange(int range);
char    			*EGB_Component_RangeSerializer(void **comp);
void                *EGB_Component_RangeUnserializer(char *raw);
int 				EGB_Component_DestroyRange();

#endif