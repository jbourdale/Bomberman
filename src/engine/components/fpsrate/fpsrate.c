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

int         set_framerate(Uint32 uframerate)
{
    entity_t                *entity;
    Uint32                  framerate;
    fpsrate_component_t     *comp;

    framerate = uframerate;
    if (!uframerate)
        framerate = DEFAULT_FRAME_RATE;

    entity = find_first_entity_by_name("fps_indicator");
    if (entity == NULL)
        return 1;
    comp = (fpsrate_component_t *)find_component_by_name(entity, "fpsrate_component");
    if (comp == NULL)
        return 1;

    comp->fpsrate = framerate;
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

