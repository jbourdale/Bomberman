/*
** bomb.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "bomb.h"


void 						place_bomb(EGB_Entity *player) 
{
	EGB_Entity 				*bomb;
	EGB_Component_Position 	*position, *player_position;

	log_debug("PLACE BOMB");

	player_position = EGB_FindComponentByName(player, "position_component");
	if (player_position == NULL)
		return ;

	bomb = EGB_Entity_Create("bomb");

	position = EGB_Component_CreatePosition(
    	player_position->x, player_position->y, EGB_Position_Top, 100, 75
	);
	EGB_Component_AddToEntity(bomb, position);

	create_bomb_animation(bomb);
	EGB_Component_StartAnimation(bomb, BOMB_ANIMATION_ID);
}