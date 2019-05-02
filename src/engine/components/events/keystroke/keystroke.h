/*
** keystroke.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __EVENT_KEYSTROKE_H__
#define __EVENT_KEYSTROKE_H__

#include "../../../engine.h"

entity_manager_t *event_keystroke_manager(Uint32 flags, ...);
event_component_t *create_event_keystroke_component(void(*f));
int destroy_event_keystroke_component(entity_t *entity);

#endif