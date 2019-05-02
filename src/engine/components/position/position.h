#ifndef __POSITION_H__
#define __POSITION_H__

#include "../../engine.h"

#define EGB_Position_Background   	INT_MIN
#define EGB_Position_AlwaysOnTop  	INT_MAX
#define EGB_Position_Classic      	0
#define EGB_Position_Top      		1024
#define EGB_Position_Bottom      	-1024

typedef struct          position_component_s
{
    char        *name;
    int         x;
    int         y;
    int         z;
    int         width;
    int         height;
}                       position_component_t;

// position.c
position_component_t *EGB_Component_CreatePosition(int x, int y, int z, int width, int height);
int EGB_Component_DestroyPosition(entity_t *entity);
int EGB_Component_PositionToRect(position_component_t *comp, SDL_Rect *rect);

// observable.c
entity_manager_t  *EGB_Observable_Position(Uint32 flags, ...);

#endif
