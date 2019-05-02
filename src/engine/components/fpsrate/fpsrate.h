/*
** fpsrate.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#ifndef __FPSRATE_H__
#define __FPSRATE_H__

#include "../../engine.h"

typedef struct          fpsrate_component_s
{
    char        		*name;
    Uint32         		fpsrate;
}                       fpsrate_component_t;

fpsrate_component_t *EGB_Component_CreateFPSRate(Uint32 framerate);
int EGB_Component_DestroyFPSRate(entity_t *entity);
int EGB_SetFramerate(Uint32 framerate);

#endif
