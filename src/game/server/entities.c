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
	handle_entity_destruction(sock, strdup(raw));
	EGBS_Serializer_DecodeEntities(raw);
    broadcast_to_players(sock, raw, player);
}


void handle_entity_destruction(int sock, char *raw) 
{
	char *token, *networkable_id;
	EGB_Entity *entity;

	raw = strtok(raw, "#");
	token = strtok(raw, EGB_NETWORK_VALUE_SEPARATOR); // NETWORK IDENTIFIER
    networkable_id = strtok(NULL, EGB_NETWORK_VALUE_SEPARATOR);
    strtok(NULL, EGB_NETWORK_VALUE_SEPARATOR);
    entity = EGBS_Network_FindEntityByNetworkId(networkable_id);
    if (entity == NULL) {
    	return ;
    }
    token = strtok(NULL, EGB_NETWORK_VALUE_SEPARATOR);
    if (strcmp(token, "destroy") == 0 && entity != NULL && strcmp(entity->name, "bomb") == 0) {
    	log_debug("BOMB HAVE BEEN DESTROYED");
    	handle_bomb_explosion(sock, entity);
    }
}