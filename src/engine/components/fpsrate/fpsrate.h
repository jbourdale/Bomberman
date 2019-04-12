#ifndef __FPSRATE_H__
#define __FPSRATE_H__

#include "../../engine.h"

typedef struct          fpsrate_component_s
{
    char        		*name;
    Uint32         		fpsrate;
}                       fpsrate_component_t;

fpsrate_component_t *create_fpsrate_component(Uint32 framerate);
int destroy_fpsrate_component(entity_t *entity);
int set_framerate(Uint32 framerate);

#endif
