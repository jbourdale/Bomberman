/*
** collision.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifdef __COLLISION_H__
#define __COLLISION_H__

#include "../../engine.h"

typedef struct 		EGB_Component_Collision_s
{
	char 			*name;
	int 			active;
}					EGB_Component_Collision;

EGB_Entity_Manager *EGB_Observable_Event_Click(Uint32 flags, ...);
EGB_Component_Collision *EGB_Component_CreateCollision(int active);
int EGB_Component_DestroyEventClick(EGB_Entity *entity);

#define