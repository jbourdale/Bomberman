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
	log_debug("DRAW: %d", draw);

	if (draw <= 20) { // 20% of chance
		create_bonus(sock, "range_bonus", x, y);
	} else if (draw >= 80) { // 20% of chance
		create_bonus(sock, "add_bomb_bonus", x, y);
	}
}

void create_bonus(int sock, char *bonus_name, int x, int y)
{
	EGB_Entity 					*range_bonus;
	EGB_Component_Position 		*position;
	EGB_Component_Networkable 	*network;
	EGB_Component_Collision 	*collision;
	char 						*encoded;

	log_debug("CREATE BONUS (%s) AT (%d, %d)", bonus_name, x, y);

	range_bonus = EGBS_Entity_Create(bonus_name);
	position = EGB_Component_CreatePosition(
		x * 100 + 350 + 25,
        y * 100 + 25,
        EGB_Position_AlwaysOnTop,
        50,
        50
	);
	network = EGB_Component_CreateNetworkable();
	collision = EGB_Component_CreateCollision(1);

	EGB_Component_AddToEntity(range_bonus, position);
	EGB_Component_AddToEntity(range_bonus, network);
	EGB_Component_AddToEntity(range_bonus, collision);

	encoded = EGB_Serializer_EncodeEntity(range_bonus);
    broadcast_to_players(sock, encoded, NULL);
}
