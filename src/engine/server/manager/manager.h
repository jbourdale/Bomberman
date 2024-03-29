/*
** manager.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __SERVER_MANAGER_H__
#define __SERVER_MANAGER_H__

#include "../../engine.h"

EGB_Entity_Manager *EGBS_Manager_Entity(Uint32 flags, ...);
EGB_Entity **EGBS_Entity_FindByName(char *name);
EGB_Entity *EGBS_FindEntityByPosition(int x, int y, int z);

#endif
