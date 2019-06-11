/*
** animations.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "animations.h"

Animation_Description bomb_anim[] = {
    { 40, 0, 0 },
    { 40, 1, 0 },
    { 40, 2, 0 },
    { 40, 3, 0 },
    { 40, 4, 0 },
    { 40, 5, 0 },
    { 40, 6, 0 },
    { 40, 7, 0 },
    { 40, 8, 0 },
    { 40, 0, 1 },
    { 40, 1, 1 },
    { 40, 2, 1 },
    { 40, 3, 1 },
    { 40, 4, 1 },
    { 40, 5, 1 },
    { 40, 6, 1 },
    { 40, 7, 1 },
    { 40, 8, 1 },
    { 40, 0, 2 },
    { 40, 1, 2 },
    { 40, 2, 2 },
    { 40, 3, 2 },
    { 40, 4, 2 },
    { 40, 5, 2 },
    { 40, 6, 2 },
    { 40, 7, 2 },
    { 40, 8, 2 },
    { 40, 0, 3 },
    { 40, 1, 3 },
    { 40, 2, 3 },
    { 40, 3, 3 },
    { 40, 4, 3 },
    { 40, 5, 3 },
    { 40, 6, 3 },
    { 40, 7, 3 },
    { 40, 8, 3 },
    { 40, 0, 4 },
    { 40, 1, 4 },
    { 40, 2, 4 },
    { 40, 3, 4 },
    { 40, 4, 4 },
    { 40, 5, 4 },
    { 40, 6, 4 },
    { 40, 7, 4 },
    { 40, 8, 4 },
    { 40, 0, 5 },
    { 40, 1, 5 },
    { 40, 2, 5 },
    { 40, 3, 5 },
    { 40, 4, 5 },
    { 40, 5, 5 },
    { 40, 6, 5 },
    { 40, 7, 5 },
    { 40, 8, 5 }
};

void on_bomb_explose(EGB_Entity *bomb) {
    EGB_Entity_Destroy(bomb);
}

void create_bomb_animation(EGB_Entity *bomb)
{
	EGB_Component_Animation *anim;
	int 	i, frame_id;

	anim = EGB_Component_CreateAnimation(
		"bomb/spritesheet.png", BOMB_ANIMATION_ID, 800, 600, EGB_Animation_NotLooping
	);

	i = 0;
	while(i < 54) {
		frame_id = EGB_Animation_AddKeyframe(anim, bomb_anim[i].duration, bomb_anim[i].x, bomb_anim[i].y);
		i++;
	}

    EGB_Keyframe_Set_OnFinish(anim, frame_id, on_bomb_explose);
	EGB_Component_AddToEntity(bomb, anim);
}

Animation_Description explosion_anim[] = {
    { 80, 0, 0 },
    { 80, 1, 0 },
    { 80, 2, 0 },
    { 80, 0, 1 },
    { 80, 1, 1 },
    { 80, 2, 1 },
    { 80, 0, 2 },
    { 80, 1, 2 },
    { 80, 2, 2 },
};

void on_explosion_over(EGB_Entity *explosion)
{
    log_debug(NULL, explosion);
    EGB_Entity_Destroy(explosion);
}

void create_explosion_animation(EGB_Entity *explosion)
{
    EGB_Component_Animation *anim;
    int i, frame_id;

    anim = EGB_Component_CreateAnimation(
        "bomb/explosion.png", EXPLOSION_ANIMATION_ID, 572, 572, EGB_Animation_NotLooping
    );

    i = 0;
    while (i < 9) {
        frame_id = EGB_Animation_AddKeyframe(
            anim, explosion_anim[i].duration, explosion_anim[i].x, explosion_anim[i].y
        );
        i++;
    }

    EGB_Keyframe_Set_OnFinish(anim, frame_id, on_explosion_over);
    EGB_Component_AddToEntity(explosion, anim);
}
