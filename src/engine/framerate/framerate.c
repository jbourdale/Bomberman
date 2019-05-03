/*
** framerate.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "framerate.h"

int EGB_fps_timer;

/**
 * @brief      Start the timer use to compute how much time the frame took to render
 */
void                        EGB_InitFPSRegulation()
{
    EGB_fps_timer = SDL_GetTicks();
}

/**
 * @brief      Wait (or not) amount of ms needed to match the setted framerate
 * 
 * @note       You can set the framerate with EGB_SetFramerate() 
 */
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