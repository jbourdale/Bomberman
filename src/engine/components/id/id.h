/*
** id.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __COMPONENT_ID_H__
#define __COMPONENT_ID_H__

#include "../../engine.h"

typedef struct          EGB_Component_Id_s
{
    char        *name;
    int         id;
}                       EGB_Component_Id;

EGB_Component_Id 	*EGB_Component_CreateId(int id);
char    			*EGB_Component_IdSerializer(void **comp);
void                *EGB_Component_IdUnserializer(char *raw);
int 				EGB_Component_DestroyId();

#endif