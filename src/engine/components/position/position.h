#ifndef __POSITION_H__
#define __POSITION_H__

#include "../../engine.h"

typedef struct          position_component_s
{
    char        *name;
    int         x;
    int         y;
    int         width;
    int         height;
}                       position_component_t;

position_component_t *create_position_component(int x, int y, int width, int height);
int destroy_position_component(entity_t *entity);
int position_component_to_rect(position_component_t *comp, SDL_Rect *rect);

#endif
