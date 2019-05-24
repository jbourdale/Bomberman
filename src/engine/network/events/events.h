/*
** events.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __NETWORK_EVENTS_H__
#define __NETWORK_EVENTS_H__

#include "../../engine.h"

typedef void (*EGB_Network_EventCallback)(char *);
typedef struct					EGB_Network_Event_s
{
	char 						*name;
	EGB_Network_EventCallback 	fn;
	struct EGB_Network_Event_s 	*next;
} 								EGB_Network_Event;

typedef struct 			EGB_Network_Event_List_s
{
	EGB_Network_Event 	*first;
}						EGB_Network_Event_List;


void EGB_Network_RegisterEvent(char *name, EGB_Network_EventCallback event);
void EGB_Network_CallEventCallback(char *event, char *payload);
void EGB_Network_ParseEventRequest(char *payload);

#endif