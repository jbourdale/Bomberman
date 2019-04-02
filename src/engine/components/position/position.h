#ifndef __POSITION_H__
#define __POSITION_H__

#include "../../engine.h"

struct          position_component_s
{
    char        *name;
    int         x;
    int         y;
    int         width;
    int         height;
} typedef       position_component_t;

position_component_t *create_position_component(int x, int y, int width, int height);

#endif
