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
	EGB_Component_Counter *nb_bomb;

	nb_bomb = EGB_FindComponentByName(bomb, "counter_component");
	if (nb_bomb != NULL)
		nb_bomb->counter--;
	EGB_Network_DestroyEntity(bomb);
}

void 							place_bomb(EGB_Entity *player) 
{
	EGB_Entity 					*bomb;
	EGB_Component_Position 		*position, *player_position;
	EGB_Component_Networkable 	*networkable;
	EGB_Component_Range 		*range, *player_range;
	EGB_Component_Counter 		*nb_bomb;
	int 						x, y;

	player_position = EGB_FindComponentByName(player, "position_component");
	player_range = EGB_FindComponentByName(player, "range_component");
	nb_bomb = EGB_FindComponentByName(player, "counter_component");
	log_debug("nb_bomb : %p", nb_bomb);
	if (player_position == NULL || player_range == NULL || nb_bomb == NULL)
		return ;

	log_debug("nb_bomb->counter : %d, max : %d", nb_bomb->counter, nb_bomb->max);
	if (nb_bomb->counter >= nb_bomb->max)
		return ;

	bomb = EGB_Entity_Create("bomb");
	bomb->on_destroy = on_bomb_destroy;
	networkable = EGB_Component_CreateNetworkable();
	networkable->owner = 0;

	x = floor(((player_position->x + player_position->width / 2) - 350) / 100) * 100 + 350;
	y = floor((player_position->y + player_position->height / 2) / 100) * 100;

	position = EGB_Component_CreatePosition(x, y, EGB_Position_Top, 100, 75);
	range = EGB_Component_CreateRange(player_range->range);

	EGB_Component_AddToEntity(bomb, position);
	EGB_Component_AddToEntity(bomb, networkable);
	EGB_Component_AddToEntity(bomb, range);
	EGB_Component_AddToEntity(bomb, nb_bomb);

	create_bomb_animation(bomb);
	EGB_Component_StartAnimation(bomb, BOMB_ANIMATION_ID);

	nb_bomb->counter++;

	EGB_Network_SendEntity(bomb);
}