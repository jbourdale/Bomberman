/*
** networkable.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __NETWORKABLE_H__
#define __NETWORKABLE_H__

#include "../../engine.h"

#define EGB_NETWORKABLE_ID_LENGTH   32

typedef struct          EGB_Component_Networkable_s
{
    char                *name;
    char                *id;
}                       EGB_Component_Networkable;

EGB_Component_Networkable   *EGB_Component_CreateNetworkable();
char                        *EGB_Network_GenerateId(char *str);
int                         EGB_Component_DestroyNetworkable(EGB_Entity *entity);

#endif
