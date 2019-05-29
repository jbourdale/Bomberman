/*
** network.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "events.h"

EGB_Network_Event_List *EGB_RegisteredNetworkEvents = NULL;
void 					EGB_Network_RegisterEvent(char *name, EGB_Network_EventCallback callback)
{
	EGB_Network_Event 	*entry, *iterator;

	entry = malloc(sizeof(EGB_Network_Event));
	entry->name = name;
	entry->fn = callback;
	entry->next = NULL;

	if (EGB_RegisteredNetworkEvents == NULL) {
		EGB_RegisteredNetworkEvents = malloc(sizeof(EGB_Network_Event_List));
		EGB_RegisteredNetworkEvents->first = entry;
		return ;
	}

	iterator = EGB_RegisteredNetworkEvents->first;
	while (iterator->next != NULL) {
		iterator = iterator->next;
	}
	iterator->next = entry;
}

void EGB_Network_CallEventCallback(char *event, char *payload)
{
	EGB_Network_Event *iterator;

	if (EGB_RegisteredNetworkEvents == NULL)
		return;

	iterator = EGB_RegisteredNetworkEvents->first;
	while (iterator != NULL && strcmp(iterator->name, event) != 0) {
		iterator = iterator->next;
	}
	if (iterator == NULL)
		return;
	iterator->fn(payload);
}

void EGB_Network_ParseEventRequest(char *payload)
{
	char *event_name;
	char *event_data;

	strtok_r(payload, EGB_NETWORK_VALUE_SEPARATOR, &payload);
	event_name = strtok_r(NULL, EGB_NETWORK_VALUE_SEPARATOR, &payload);
	event_data = strtok_r(NULL, EGB_NETWORK_VALUE_SEPARATOR, &payload);

	EGB_Network_CallEventCallback(event_name, event_data);
}
