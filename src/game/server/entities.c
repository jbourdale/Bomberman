/*
** entities.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "server.h"

void handle_entities_request(int sock, char *raw, player_t *player) 
{
	handle_entity_destruction(strdup(raw));
	EGBS_Serializer_DecodeEntities(raw);
    broadcast_to_players(sock, raw, player);
}


void handle_entity_destruction(char *raw) 
{
	char *token, *networkable_id;
	EGB_Entity *entity;

	raw = strtok(raw, "#");
	log_debug("handle_entity_destruction");
	token = strtok(raw, EGB_NETWORK_VALUE_SEPARATOR); // NETWORK IDENTIFIER
	log_debug("network identifier : %s", token);
    networkable_id = strtok(NULL, EGB_NETWORK_VALUE_SEPARATOR);
	log_debug("network id : %s", networkable_id);
    strtok(NULL, EGB_NETWORK_VALUE_SEPARATOR);
    entity = EGBS_Network_FindEntityByNetworkId(networkable_id);
    if (entity == NULL) {
    	log_debug("Entity not founded for id %s", networkable_id);
    	return ;
    }
    log_debug("founded entity : %s", entity->name);
    token = strtok(NULL, EGB_NETWORK_VALUE_SEPARATOR);
    log_debug("token : %s", token);
    if (strcmp(token, "destroy") == 0 && entity != NULL && strcmp(entity->name, "bomb") == 0) {
    	log_debug("BOMB HAVE BEEN DESTROYED");
    }
}