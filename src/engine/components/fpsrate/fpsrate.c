/*
** fpsrate.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "fpsrate.h"

EGB_Component_FPSRate    *EGB_Component_CreateFPSRate(Uint32 fpsrate)
{
    EGB_Component_FPSRate    *component;

    component = malloc(sizeof(EGB_Component_FPSRate));
    component->name = strdup("fpsrate_component");
    component->fpsrate = fpsrate;
    return component;
}

int         EGB_SetFramerate(Uint32 uframerate)
{
    EGB_Entity                *entity;
    Uint32                  framerate;
    EGB_Component_FPSRate     *comp;

    framerate = uframerate;
    if (!uframerate)
        framerate = DEFAULT_FRAME_RATE;

    entity = EGB_Entity_FindFirstByName("fps_indicator");
    if (entity == NULL)
        return 1;
    comp = (EGB_Component_FPSRate *)EGB_FindComponentByName(entity, "fpsrate_component");
    if (comp == NULL)
        return 1;

    comp->fpsrate = framerate;
    return 0;
}

int                         EGB_Component_DestroyFPSRate(EGB_Entity *entity)
{
    EGB_Component_Position    *comp;

    comp = (EGB_Component_Position *)EGB_FindComponentByName(entity, "fpsrate_component");
    if (comp == NULL)
        return 1;

    //free(comp);
    return 0;
}

