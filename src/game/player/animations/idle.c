/*
** idle.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "animations.h"

Animation_Description back_dying[] = {
    { 40, 0, 0 },
    { 40, 1, 0 },
    { 40, 2, 0 },
    { 40, 3, 0 },
    { 40, 4, 0 },
    { 40, 5, 0 },
};

Animation_Description back_idle[] = {
    { 40, 6, 0 },
    { 40, 7, 0 },
    { 40, 8, 0 },
    { 40, 9, 0 },
    { 40, 10, 0 },
    { 40, 11, 0 },
    { 40, 12, 0 },
    { 40, 13, 0 },
    { 40, 0, 1 },
    { 40, 1, 1 },
    { 40, 2, 1 },
    { 40, 3, 1 },
    { 40, 4, 1 },
    { 40, 5, 1 },
    { 40, 6, 1 },
    { 40, 7, 1 },
    { 40, 8, 1 },
    { 40, 9, 1 }
};


Animation_Description front_dying[] = {
    { 40, 0, 3 },
    { 40, 1, 3 },
    { 40, 2, 3 },
    { 40, 3, 3 },
    { 40, 4, 3 },
    { 40, 5, 3 }
};

Animation_Description front_idle[] = {
    { 40, 6, 3 },
    { 40, 7, 3 },
    { 40, 8, 3 },
    { 40, 9, 3 },
    { 40, 10, 3 },
    { 40, 11, 3 },
    { 40, 12, 3 },
    { 40, 13, 3 },
    { 40, 0, 4 },
    { 40, 1, 4 },
    { 40, 2, 4 },
    { 40, 3, 4 },
    { 40, 4, 4 },
    { 40, 5, 4 },
    { 40, 6, 4 },
    { 40, 7, 4 },
    { 40, 8, 4 },
    { 40, 9, 4 }
};



Animation_Description left_dying[] = {
    { 40, 0, 6 },
    { 40, 1, 6 },
    { 40, 2, 6 },
    { 40, 3, 6 },
    { 40, 4, 6 },
    { 40, 5, 6 }
};

Animation_Description left_idle[] = {
    { 40, 6, 6 },
    { 40, 7, 6 },
    { 40, 8, 6 },
    { 40, 9, 6 },
    { 40, 10, 6 },
    { 40, 11, 6 },
    { 40, 12, 6 },
    { 40, 13, 6 },
    { 40, 0, 7 },
    { 40, 1, 7 },
    { 40, 2, 7 },
    { 40, 3, 7 },
    { 40, 4, 7 },
    { 40, 5, 7 },
    { 40, 6, 7 },
    { 40, 7, 7 },
    { 40, 8, 7 },
    { 40, 9, 7 }
};



Animation_Description right_dying[] = {
    { 40, 0, 9 },
    { 40, 1, 9 },
    { 40, 2, 9 },
    { 40, 3, 9 },
    { 40, 4, 9 },
    { 40, 5, 9 }
};

Animation_Description right_idle[] = {
    { 40, 6, 9 },
    { 40, 7, 9 },
    { 40, 8, 9 },
    { 40, 9, 9 },
    { 40, 10, 9 },
    { 40, 11, 9 },
    { 40, 12, 9 },
    { 40, 13, 9 },
    { 40, 0, 10 },
    { 40, 1, 10 },
    { 40, 2, 10 },
    { 40, 3, 10 },
    { 40, 4, 10 },
    { 40, 5, 10 },
    { 40, 6, 10 },
    { 40, 7, 10 },
    { 40, 8, 10 },
    { 40, 9, 10 }
};

void add_idle_animations(EGB_Entity *player) 
{
	EGB_Component_Animation *back, *front, *left, *right;
    char                    *spritesheet;

    spritesheet = get_player_spritesheet(player);

	back = EGB_Component_CreateAnimation(
        spritesheet, BACK_IDLE_ANIMATION_ID, 512, 512, EGB_Animation_Looping
    );
    add_animation_keyframes(back, back_idle, 18);
    EGB_Component_AddToEntity(player, back);

    front = EGB_Component_CreateAnimation(
        spritesheet, FRONT_IDLE_ANIMATION_ID, 512, 512, EGB_Animation_Looping
    );
    add_animation_keyframes(front, front_idle, 18);
    EGB_Component_AddToEntity(player, front);

    left = EGB_Component_CreateAnimation(
        spritesheet, LEFT_IDLE_ANIMATION_ID, 512, 512, EGB_Animation_Looping
    );
    add_animation_keyframes(left, left_idle, 18);
    EGB_Component_AddToEntity(player, left);

    right = EGB_Component_CreateAnimation(
        spritesheet, RIGHT_IDLE_ANIMATION_ID, 512, 512, EGB_Animation_Looping
    );
    add_animation_keyframes(right, right_idle, 18);
    EGB_Component_AddToEntity(player, right);
}