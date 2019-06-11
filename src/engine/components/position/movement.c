/*
** movement.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "position.h"


/**
 * @brief      Check if the entity can access his current position
 *
 * @param      entity  The entity
 *
 * @return     status <ul><li>0 : Can't move</li><li>1 : Can move</li></ul>
 */
int EGB_Position_Movable(EGB_Entity *entity)
{
	EGB_Component_Collision	*entity_collide_comp;
	EGB_Component_Position	*entity_position_comp, collide_pos_comp;
	EGB_Entity 				*tmp;

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
	if (
		entity_collide_comp != NULL &&
		entity_collide_comp->active == 1 &&
		EGB_Collide(entity, &collide_pos_comp, &tmp)
	) {
		return 0;
	}
	return 1;
}

/**
 * @brief      Move a entity to left
 *
 * @param      entity  The entity
 * @param  	   offset  The offset
 *
 * @return     status <ul><li>0: Successfuly move</li><li>1: An error occured</li></ul>
 */
int EGB_Position_Move_Left(EGB_Entity *entity, int offset)
{
	EGB_Component_Position	*entity_position_comp;
	entity_position_comp = (EGB_Component_Position *)EGB_FindComponentByName(
		entity,
		"position_component"
	);
	if (entity_position_comp == NULL)
		return 1;
	entity_position_comp->x -= offset;
	if (!EGB_Position_Movable(entity)) {
		entity_position_comp->x += offset;
		return 1;
	}
	return 0;
}

/**
 * @brief      Move a entity to right
 *
 * @param      entity  The entity
 * @param  	   offset  The offset
 *
 * @return     status <ul><li>0: Successfuly move</li><li>1: An error occured</li></ul>
 */
int EGB_Position_Move_Right(EGB_Entity *entity, int offset)
{
	EGB_Component_Position	*entity_position_comp;
	entity_position_comp = (EGB_Component_Position *)EGB_FindComponentByName(
		entity,
		"position_component"
	);
	if (entity_position_comp == NULL)
		return 1;
	entity_position_comp->x += offset;
	if (!EGB_Position_Movable(entity)) {
		entity_position_comp->x -= offset;
		return 1;
	}
	return 0;
}

/**
 * @brief      Move a entity up
 *
 * @param      entity  The entity
 * @param  	   offset  The offset
 *
 * @return     status <ul><li>0: Successfuly move</li><li>1: An error occured</li></ul>
 */
int EGB_Position_Move_Up(EGB_Entity *entity, int offset)
{
	EGB_Component_Position	*entity_position_comp;
	entity_position_comp = (EGB_Component_Position *)EGB_FindComponentByName(
		entity,
		"position_component"
	);
	if (entity_position_comp == NULL)
		return 1;
	entity_position_comp->y -= offset;
	if (!EGB_Position_Movable(entity)) {
		entity_position_comp->y += offset;
		return 1;
	}
	return 0;
}

/**
 * @brief      Move a entity down
 *
 * @param      entity  The entity
 * @param  	   offset  The offset
 *
 * @return     status <ul><li>0: Successfuly move</li><li>1: An error occured</li></ul>
 */
int EGB_Position_Move_Down(EGB_Entity *entity, int offset)
{
	EGB_Component_Position	*entity_position_comp;
	entity_position_comp = (EGB_Component_Position *)EGB_FindComponentByName(
		entity,
		"position_component"
	);
	if (entity_position_comp == NULL)
		return 1;
	entity_position_comp->y += offset;
	if (!EGB_Position_Movable(entity)) {
		entity_position_comp->y -= offset;
		return 1;
	}
	return 0;
}
