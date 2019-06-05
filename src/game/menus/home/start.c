/*
** home.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "home.h"
#include "../../game.h"

Animation_Description countdown_anim[] = {
    { 1000, 0, 2 },
    { 1000, 0, 1 },
    { 1000, 0, 0 },
    { 1000, 0, 3 }
};

void create_start_countdown()
{
	EGB_Entity *start_countdown;
	EGB_Component_Position *pos;
	EGB_Component_Animation *anim;
	int i, frame_id;


	start_countdown = EGB_Entity_Create("start_countdown");
	pos = EGB_Component_CreatePosition(610, 440, EGB_Position_AlwaysOnTop, 700, 200);

	anim = EGB_Component_CreateAnimation(
		"menus/start_countdown.png", START_COUNTDOWN_ANIMATION_ID, 700, 200, EGB_Animation_NotLooping
	);

	i = 0;
	while(i < 4) {
		frame_id = EGB_Animation_AddKeyframe(anim, countdown_anim[i].duration, countdown_anim[i].x, countdown_anim[i].y);
		i++;
	}

    EGB_Keyframe_Set_OnFinish(anim, frame_id, bind_my_player);
	EGB_Component_AddToEntity(start_countdown, anim);
	EGB_Component_AddToEntity(start_countdown, pos);

	EGB_Component_StartAnimation(start_countdown, START_COUNTDOWN_ANIMATION_ID);
}