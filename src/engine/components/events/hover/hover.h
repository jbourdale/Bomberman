/*
** hover.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __EVENT_HOVER_H__
#define __EVENT_HOVER_H__

#include "../../../engine.h"

entity_manager_t *EGB_Observable_Event_Hover(Uint32 flags, ...);
event_component_t *EGB_Component_CreateEventHover(void(*f));
int EGB_Component_DestroyEventHover(entity_t *entity);

#endif