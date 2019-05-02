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

position_component_t *create_position_component(int x, int y, int z, int width, int height);
int destroy_position_component(entity_t *entity);
int position_component_to_rect(position_component_t *comp, SDL_Rect *rect);
entity_manager_t  *entities_position_manager(Uint32 flags, ...);

#endif
