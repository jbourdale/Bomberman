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

entity_manager_t *event_hover_manager(Uint32 flags, ...);
event_component_t *create_event_hover_component(void(*f));
int destroy_event_hover_component(entity_t *entity);

#endif