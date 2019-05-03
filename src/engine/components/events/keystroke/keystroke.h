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

EGB_Entity_Manager *EGB_Observable_Event_KeyStroke(Uint32 flags, ...);
EGB_Component_Event *EGB_Component_CreateEventKeyStroke(void(*f));
int EGB_Component_DestroyEventKeyStroke(EGB_Entity *entity);

#endif