/*
** collision.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "../../engine.h"

typedef struct 		EGB_Component_Collision_s
{
	char 			*name;
	int 			active;
}					EGB_Component_Collision;


EGB_Entity_Manager      *EGB_Manager_Collision(Uint32 flags, ...);
EGB_Component_Collision *EGB_Component_CreateCollision(int active);
int                     EGB_Component_DestroyCollision(EGB_Entity *entity);
int                     EGB_Collide(EGB_Entity *entity, EGB_Component_Position *collision);
char                    *EGB_Component_CollisionSerializer(void **comp);
void                    *EGB_Component_CollisionUnserializer(char *raw);

#endif
