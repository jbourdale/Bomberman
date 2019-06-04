/*
** bomb.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "../requests/requests.h"
#include "state.h"


void generate_bonus(int sock, int x, int y)
{
	int draw;

	draw = floor(rand() % (100));

	if (draw <= 20) { // 20% of chance
		create_range_bonus(sock, x, y);
	} else if (draw >= 80) { // 20% of chance
		log_debug("create nb bomb bonus");
	}
}

void create_range_bonus(int sock, int x, int y)
{
	EGB_Entity 					*range_bonus;
	EGB_Component_Position 		*position;
	EGB_Component_Networkable 	*network;
	char 						*encoded;

	log_debug("CREATE RANGE BONUS AT (%d, %d)", x, y);

	range_bonus = EGBS_Entity_Create("range_bonus");
	position = EGB_Component_CreatePosition(
		x * 100 + 350 + 25,
        y * 100 + 25,
        EGB_Position_AlwaysOnTop,
        50,
        50
	);
	network = EGB_Component_CreateNetworkable();

	EGB_Component_AddToEntity(range_bonus, position);
	EGB_Component_AddToEntity(range_bonus, network);

	encoded = EGB_Serializer_EncodeEntity(range_bonus);
    broadcast_to_players(sock, encoded, NULL);
}