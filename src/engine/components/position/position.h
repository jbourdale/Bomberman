/*
** position.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#ifndef __POSITION_H__
#define __POSITION_H__

#include "../../engine.h"

#define EGB_Position_Background   	INT_MIN
#define EGB_Position_AlwaysOnTop  	INT_MAX
#define EGB_Position_Classic      	0
#define EGB_Position_Top      		1024
#define EGB_Position_Bottom      	-1024

typedef struct          EGB_Component_Position_s
{
    char        *name;
    int         x;
    int         y;
    int         z;
    int         width;
    int         height;
}                       EGB_Component_Position;

// position.c
EGB_Component_Position *EGB_Component_CreatePosition(int x, int y, int z, int width, int height);
int EGB_Component_DestroyPosition(EGB_Entity *entity);
int EGB_Component_PositionToRect(EGB_Component_Position *comp, SDL_Rect *rect);

// observable.c
EGB_Entity_Manager  *EGB_Observable_Position(Uint32 flags, ...);

// movement.c
int EGB_Position_Move_Left(EGB_Entity *entity, int offset);
int EGB_Position_Move_Right(EGB_Entity *entity, int offset);
int EGB_Position_Move_Up(EGB_Entity *entity, int offset);
int EGB_Position_Move_Down(EGB_Entity *entity, int offset);

#endif
