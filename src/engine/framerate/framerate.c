/*
** framerate.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "framerate.h"

int EGB_fps_timer;

void                        EGB_InitFPSRegulation()
{
    EGB_fps_timer = SDL_GetTicks();
}

void                        EGB_RegulateFPS()
{
    EGB_Entity                *entity;
    EGB_Component_FPSRate     *comp;

    entity = EGB_Entity_FindFirstByName("fps_indicator");
    if (entity == NULL)
        return ;
    comp = (EGB_Component_FPSRate *)EGB_FindComponentByName(entity, "fpsrate_component");
    if (comp == NULL)
        return ;

    if ( (SDL_GetTicks() - EGB_fps_timer) < 1000 / comp->fpsrate ) {
        SDL_Delay((1000 / comp->fpsrate) - (SDL_GetTicks() - EGB_fps_timer));
    }
}