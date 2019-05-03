/*
** click.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __EVENT_CLICK_H__
#define __EVENT_CLICK_H__

#include "../../../engine.h"

EGB_Entity_Manager *EGB_Observable_Event_Click(Uint32 flags, ...);
EGB_Component_Event *EGB_Component_CreateEventClick(void(*f));
int EGB_Component_DestroyEventClick(EGB_Entity *entity);

#endif