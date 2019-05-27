/*
** idle.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "animations.h"

void add_idle_animation(EGB_Entity *player) 
{
	EGB_Component_Animation *animation_comp;

	animation_comp = EGB_Component_CreateAnimation(
        "player.png", 0, 614, 564, 1
    );
    EGB_Animation_AddKeyframe(animation_comp, 40, 0, 0);
    EGB_Animation_AddKeyframe(animation_comp, 40, 1, 0);
    EGB_Animation_AddKeyframe(animation_comp, 40, 2, 0);
    EGB_Animation_AddKeyframe(animation_comp, 40, 3, 0);
    EGB_Animation_AddKeyframe(animation_comp, 40, 4, 0);
    EGB_Animation_AddKeyframe(animation_comp, 40, 5, 0);
    EGB_Animation_AddKeyframe(animation_comp, 40, 6, 0);
    EGB_Animation_AddKeyframe(animation_comp, 40, 7, 0);
    EGB_Animation_AddKeyframe(animation_comp, 40, 8, 0);
    EGB_Animation_AddKeyframe(animation_comp, 40, 9, 0);
    EGB_Animation_AddKeyframe(animation_comp, 40, 10, 0);
    EGB_Animation_AddKeyframe(animation_comp, 40, 11, 0);
    EGB_Animation_AddKeyframe(animation_comp, 40, 12, 0);
    EGB_Animation_AddKeyframe(animation_comp, 40, 13, 0);
    EGB_Animation_AddKeyframe(animation_comp, 40, 14, 0);

    EGB_Component_AddToEntity(player, animation_comp);
    EGB_Component_StartAnimation(player, 0);
}