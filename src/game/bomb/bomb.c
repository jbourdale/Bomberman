/*
** bomb.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "bomb.h"

void on_bomb_destroy(EGB_Entity *bomb) 
{
	EGB_Network_DestroyEntity(bomb);
}

void 							place_bomb(EGB_Entity *player) 
{
	EGB_Entity 					*bomb;
	EGB_Component_Position 		*position, *player_position;
	EGB_Component_Networkable 	*networkable;
	EGB_Component_Range 		*range, *player_range;
	int 						x, y;

	player_position = EGB_FindComponentByName(player, "position_component");
	player_range = EGB_FindComponentByName(player, "range_component");
	if (player_position == NULL || player_range == NULL)
		return ;

	bomb = EGB_Entity_Create("bomb");
	bomb->on_destroy = on_bomb_destroy;
	networkable = EGB_Component_CreateNetworkable();

	x = floor(((player_position->x + player_position->width / 2) - 350) / 100) * 100 + 350;
	y = floor((player_position->y + player_position->height / 2) / 100) * 100;

	position = EGB_Component_CreatePosition(x, y, EGB_Position_Top, 100, 75);
	range = EGB_Component_CreateRange(player_range->range);

	EGB_Component_AddToEntity(bomb, position);
	EGB_Component_AddToEntity(bomb, networkable);
	EGB_Component_AddToEntity(bomb, range);

	create_bomb_animation(bomb);
	EGB_Component_StartAnimation(bomb, BOMB_ANIMATION_ID);

	EGB_Network_SendEntity(bomb);
}