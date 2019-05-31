/*
** movement.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "velocity.h"

void 						EGB_Entity_HandleVelocity(EGB_Entity *entity)
{
	EGB_Component_Velocity 	*velocity;

	velocity = EGB_FindComponentByName(entity, "velocity_component");

	if (velocity == NULL) {
		return;
	}

	if (velocity->x > 0) {
		EGB_Position_Move_Right(entity, velocity->x);
	}
	else if (velocity->x < 0) {
		EGB_Position_Move_Left(entity, -velocity->x);
	}

	if (velocity->y > 0) {
		EGB_Position_Move_Down(entity, velocity->y);
	}
	else if (velocity->y < 0) {
		EGB_Position_Move_Up(entity, -velocity->y);
	}
}