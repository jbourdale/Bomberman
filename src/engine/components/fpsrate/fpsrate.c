/*
** fpsrate.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "fpsrate.h"

fpsrate_component_t    *create_fpsrate_component(Uint32 fpsrate)
{
    fpsrate_component_t    *component;

    component = malloc(sizeof(fpsrate_component_t));
    component->name = strdup("fpsrate_component");
    component->fpsrate = fpsrate;
    return component;
}

int         set_framerate(Uint32 framerate)
{
    entity_t                *entity;
    fpsrate_component_t     *comp;

    if (!framerate)
        framerate = DEFAULT_FRAME_RATE;
    
    log_debug("set_framerate : %d", framerate);

    entity = find_first_entity_by_name("fps_indicator");
    if (entity == NULL)
        return 1;
    comp = (fpsrate_component_t *)find_component_by_name(entity, "fpsrate_component");
    if (comp == NULL)
        return 1;

    log_debug("setting fpsrate to %d", framerate);
    comp->fpsrate = framerate;
    log_debug("set_framerate end");
    return 0;
}

int                         destroy_fpsrate_component(entity_t *entity)
{
    position_component_t    *comp;

    comp = (position_component_t *)find_component_by_name(entity, "fpsrate_component");
    if (comp == NULL)
        return 1;

    free(comp);
    return 0;
}

