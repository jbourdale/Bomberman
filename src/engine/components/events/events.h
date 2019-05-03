/*
** event.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __EVENT_COMPONENT_H__
#define __EVENT_COMPONENT_H__

typedef struct          EGB_Component_Event_s
{
    char        		*name;
    void 				(*f)();
}                       EGB_Component_Event;

#endif