/*
** velocity.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __COMPONENT_VELOCITY_H__
#define __COMPONENT_VELOCITY_H__

#include "../../engine.h"

typedef struct          EGB_Component_Velocity_s
{
    char        *name;
    int         x;
    int         y;
}                       EGB_Component_Velocity;

EGB_Component_Velocity 	*EGB_Component_CreateVelocity(int x, int y);
char    				*EGB_Component_VelocitySerializer(void **comp);
void                	*EGB_Component_VelocityUnserializer(char *raw);
int 					EGB_Component_DestroyVelocity();
void 					EGB_Entity_HandleVelocity(EGB_Entity *entity);
void 					EGB_Component_Velocity_SetX(EGB_Entity *entity, int x);
void 					EGB_Component_Velocity_SetY(EGB_Entity *entity, int y);

#endif