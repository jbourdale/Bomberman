/*
** entities.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "requests.h"


void destroy_entity(int sock, EGB_Entity *entity) 
{
	char *payload;
	EGB_Component_Networkable *networkable_comp;

	networkable_comp = EGB_FindComponentByName(entity, "networkable_component");
	if (networkable_comp == NULL)
		return; 

    payload = malloc(1000);
    payload[0] = EGB_ENTITY_NETWORK_IDENTIFIER;
    payload[1] = EGB_NETWORK_VALUE_SEPARATOR_CHAR;
    payload[2] = '\0';
    strcat(payload, networkable_comp->id);
    strcat(payload, EGB_NETWORK_VALUE_SEPARATOR);
    strcat(payload, "0"); // network ownership 
    strcat(payload, EGB_NETWORK_VALUE_SEPARATOR);
    strcat(payload, "destroy#");

    broadcast_to_players(sock, payload, NULL);
	EGBS_Entity_Destroy(entity);
}
