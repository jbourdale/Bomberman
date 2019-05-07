/*
** movement.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "position.h"

int EGB_Position_Movable(EGB_Entity *entity)
{
	EGB_Component_Collision	*entity_collide_comp;
	EGB_Component_Position	*entity_position_comp, collide_position_comp;

	entity_position_comp = (EGB_Component_Position *)EGB_FindComponentByName(
		entity,
		"position_component"
	);
	if (entity_position_comp == NULL)
		return 0;

	entity_collide_comp = (EGB_Component_Collision*) EGB_FindComponentByName(
		entity,
		"collision_component"
	);
	log_debug("entity_collide_comp == NULL : %d", entity_collide_comp == NULL);
	if (entity_collide_comp != NULL && entity_collide_comp->active == 1) {
		if (EGB_Collide(entity, &collide_position_comp)) {
			return 0;
		}
	}
	return 1;
}

int EGB_Position_Move_Left(EGB_Entity *entity, int offset)
{
	EGB_Component_Position	*entity_position_comp;
	entity_position_comp = (EGB_Component_Position *)EGB_FindComponentByName(
		entity,
		"position_component"
	);
	entity_position_comp->x -= offset;
	if (!EGB_Position_Movable(entity)) {
		entity_position_comp->x += offset;
		return 0;
	}
	return 1;
}

int EGB_Position_Move_Right(EGB_Entity *entity, int offset)
{
	EGB_Component_Position	*entity_position_comp;
	entity_position_comp = (EGB_Component_Position *)EGB_FindComponentByName(
		entity,
		"position_component"
	);
	entity_position_comp->x += offset;
	if (!EGB_Position_Movable(entity)) {
		entity_position_comp->x -= offset;
		return 0;
	}
	return 1;
}

int EGB_Position_Move_Up(EGB_Entity *entity, int offset)
{
	EGB_Component_Position	*entity_position_comp;
	entity_position_comp = (EGB_Component_Position *)EGB_FindComponentByName(
		entity,
		"position_component"
	);
	entity_position_comp->y -= offset;
	if (!EGB_Position_Movable(entity)) {
		entity_position_comp->y += offset;
		return 1;
	}
	return 0;
}

int EGB_Position_Move_Down(EGB_Entity *entity, int offset)
{
	EGB_Component_Position	*entity_position_comp;
	entity_position_comp = (EGB_Component_Position *)EGB_FindComponentByName(
		entity,
		"position_component"
	);
	entity_position_comp->y += offset;
	if (!EGB_Position_Movable(entity)) {
		entity_position_comp->y -= offset;
		return 1;
	}
	return 0;
}
