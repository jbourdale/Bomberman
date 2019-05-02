/*
** event.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __EVENT_COMPONENT_H__
#define __EVENT_COMPONENT_H__

typedef struct          event_component_s
{
    char        		*name;
    void 				(*f)();
}                       event_component_t;

#endif