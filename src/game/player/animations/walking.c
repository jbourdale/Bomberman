/*
** walking.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "animations.h"

Animation_Description back_walking[] = {
    { 10, 10, 1 },
    { 10, 11, 1 },
    { 10, 12, 1 },
    { 10, 13, 1 },
    { 10, 0, 2 },
    { 10, 1, 2 },
    { 10, 2, 2 },
    { 10, 3, 2 },
    { 10, 4, 2 },
    { 10, 5, 2 },
    { 10, 6, 2 },
    { 10, 7, 2 },
    { 10, 8, 2 },
    { 10, 9, 2 },
    { 10, 10, 2 },
    { 10, 11, 2 },
    { 10, 12, 2 },
    { 10, 13, 2 }
};

Animation_Description front_walking[] = {
    { 10, 10, 4 },
    { 10, 11, 4 },
    { 10, 12, 4 },
    { 10, 13, 4 },
    { 10, 0, 5 },
    { 10, 1, 5 },
    { 10, 2, 5 },
    { 10, 3, 5 },
    { 10, 4, 5 },
    { 10, 5, 5 },
    { 10, 6, 5 },
    { 10, 7, 5 },
    { 10, 8, 5 },
    { 10, 9, 5 },
    { 10, 10, 5 },
    { 10, 11, 5 },
    { 10, 12, 5 },
    { 10, 13, 5 }
};

Animation_Description left_walking[] = {
    { 10, 10, 7 },
    { 10, 11, 7 },
    { 10, 12, 7 },
    { 10, 13, 7 },
    { 10, 0, 8 },
    { 10, 1, 8 },
    { 10, 2, 8 },
    { 10, 3, 8 },
    { 10, 4, 8 },
    { 10, 5, 8 },
    { 10, 6, 8 },
    { 10, 7, 8 },
    { 10, 8, 8 },
    { 10, 9, 8 },
    { 10, 10, 8 },
    { 10, 11, 8 },
    { 10, 12, 8 },
    { 10, 13, 8 }
};

Animation_Description right_walking[] = {
    { 10, 10, 10 },
    { 10, 11, 10 },
    { 10, 12, 10 },
    { 10, 13, 10 },
    { 10, 0, 11 },
    { 10, 1, 11 },
    { 10, 2, 11 },
    { 10, 3, 11 },
    { 10, 4, 11 },
    { 10, 5, 11 },
    { 10, 6, 11 },
    { 10, 7, 11 },
    { 10, 8, 11 },
    { 10, 9, 11 },
    { 10, 10, 11 },
    { 10, 11, 11 },
    { 10, 12, 11 },
    { 10, 13, 11 }
};

void add_walking_animations(EGB_Entity *player)
{
	EGB_Component_Animation *back, *front, *left, *right;
    char                    *spritesheet;

    spritesheet = get_player_spritesheet(player);

	back = EGB_Component_CreateAnimation(
        spritesheet, BACK_WALKING_ANIMATION_ID, 512, 512, EGB_Animation_Looping
    );
    add_animation_keyframes(back, back_walking, 18);
    EGB_Component_AddToEntity(player, back);

    front = EGB_Component_CreateAnimation(
        spritesheet, FRONT_WALKING_ANIMATION_ID, 512, 512, EGB_Animation_Looping
    );
    add_animation_keyframes(front, front_walking, 18);
    EGB_Component_AddToEntity(player, front);

    left = EGB_Component_CreateAnimation(
        spritesheet, LEFT_WALKING_ANIMATION_ID, 512, 512, EGB_Animation_Looping
    );
    add_animation_keyframes(left, left_walking, 18);
    EGB_Component_AddToEntity(player, left);

    right = EGB_Component_CreateAnimation(
        spritesheet, RIGHT_WALKING_ANIMATION_ID, 512, 512, EGB_Animation_Looping
    );
    add_animation_keyframes(right, right_walking, 18);
    EGB_Component_AddToEntity(player, right);
}