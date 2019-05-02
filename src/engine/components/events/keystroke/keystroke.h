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

entity_manager_t *EGB_Observable_Event_KeyStroke(Uint32 flags, ...);
event_component_t *EGB_Component_CreateEventKeyStroke(void(*f));
int EGB_Component_DestroyEventKeyStroke(entity_t *entity);

#endif