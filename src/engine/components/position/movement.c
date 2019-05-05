/*
** movement.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "position.h"

int EGB_Position_Move_Left(EGB_Entity *entity, int offset)
{
	EGB_Component_Collide	*entity_collide_comp;
	EGB_Component_Position	*entity_position_comp;

	entity_position_comp = (EGB_Component_Position *)E EGB_FindComponentByName(
		entity,
		"position_component"
	);
	if (entity_position_comp == NULL)
		return 1;

	entity_position_comp->x -= offset;
	entity_collide_comp = (EGB_Component_Collide*) EGB_FindComponentByName(
		entity,
		"collide_component"
	);
	if (entity_collide_comp != NULL && entity_collide_comp->active == 1) {
		if (EGB_Collide(entity)) {
			
		}
	}

}

int EGB_Position_Move_Right(EGB_Entity *entity, int offset)
{
	EGB_Component_Collide	*entity_collide_comp;
	EGB_Component_Position	*entity_position_comp;

	entity_position_comp = (EGB_Component_Position *)E EGB_FindComponentByName(
		entity,
		"position_component"
	);
	if (entity_position_comp == NULL)
		return 1;

	entity_position_comp->x += offset;
	entity_collide_comp = (EGB_Component_Collide*) EGB_FindComponentByName(
		entity,
		"collide_component"
	);
	if (entity_collide_comp != NULL && entity_collide_comp->active == 1) {
		if (EGB_Collide(entity)) {
			
		}
	}

}

int EGB_Position_Move_Up(EGB_Entity *entity, int offset)
{
	EGB_Component_Collide	*entity_collide_comp;
	EGB_Component_Position	*entity_position_comp;

	entity_position_comp = (EGB_Component_Position *)E EGB_FindComponentByName(
		entity,
		"position_component"
	);
	if (entity_position_comp == NULL)
		return 1;

	entity_position_comp->y -= offset;
	entity_collide_comp = (EGB_Component_Collide*) EGB_FindComponentByName(
		entity,
		"collide_component"
	);
	if (entity_collide_comp != NULL && entity_collide_comp->active == 1) {
		if (EGB_Collide(entity)) {
			
		}
	}

}

int EGB_Position_Move_Down(EGB_Entity *entity, int offset)
{
	EGB_Component_Collide	*entity_collide_comp;
	EGB_Component_Position	*entity_position_comp;

	entity_position_comp = (EGB_Component_Position *)E EGB_FindComponentByName(
		entity,
		"position_component"
	);
	if (entity_position_comp == NULL)
		return 1;

	entity_position_comp->y += offset;
	entity_collide_comp = (EGB_Component_Collide*) EGB_FindComponentByName(
		entity,
		"collide_component"
	);
	if (entity_collide_comp != NULL && entity_collide_comp->active == 1) {
		if (EGB_Collide(entity)) {
			
		}
	}

}
