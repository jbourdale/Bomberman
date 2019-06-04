/*
** bonus.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "bonus.h"

Animation_Description range_bonus_anim[] = {
    { 80, 0, 0 },
    { 80, 1, 0 },
    { 80, 2, 0 },
    { 80, 3, 0 },
    { 80, 4, 0 },
    { 80, 0, 1 },
    { 80, 1, 1 },
    { 80, 2, 1 },
    { 80, 3, 1 },
    { 80, 4, 1 },
    { 80, 0, 2 },
    { 80, 1, 2 },
    { 80, 2, 2 },
    { 80, 3, 2 },
    { 80, 4, 2 },
    { 80, 0, 3 },
    { 80, 1, 3 },
    { 80, 2, 3 },
    { 80, 3, 3 }
};

void create_range_bonus_animation(EGB_Entity *bonus) 
{
	EGB_Component_Animation *anim;
	int 	i;

	anim = EGB_Component_CreateAnimation(
		"bonus/bomb_range.png", RANGE_BONUS_ANIMATION_ID, 100, 100, EGB_Animation_Looping
	);

	i = 0;
	while(i < 19) {
		EGB_Animation_AddKeyframe(anim, range_bonus_anim[i].duration, range_bonus_anim[i].x, range_bonus_anim[i].y);
		i++;
	}

	EGB_Component_AddToEntity(bonus, anim);
}


void collect_range_bonus(EGB_Entity *player, EGB_Entity *bonus)
{
    EGB_Component_Range *range;

    range = EGB_FindComponentByName(player, "range_component");
    range->range += 1;

    EGB_Network_DestroyEntity(bonus);
    EGB_Entity_Destroy(bonus);

}


Animation_Description add_bomb_bonus_anim[] = {
    { 80, 0, 0 },
    { 80, 1, 0 },
    { 80, 2, 0 },
    { 80, 3, 0 },
    { 80, 4, 0 },
    { 80, 0, 1 },
    { 80, 1, 1 },
    { 80, 2, 1 },
    { 80, 3, 1 },
    { 80, 4, 1 },
    { 80, 0, 2 },
    { 80, 1, 2 },
    { 80, 2, 2 },
    { 80, 3, 2 },
    { 80, 4, 2 },
    { 80, 0, 3 },
    { 80, 1, 3 },
    { 80, 2, 3 },
    { 80, 3, 3 },
    { 80, 4, 3 },
    { 80, 0, 4 },
    { 80, 1, 4 },
    { 80, 2, 4 },
    { 80, 3, 4 }
};

void create_add_bomb_bonus_animation(EGB_Entity *bonus) 
{
    EGB_Component_Animation *anim;
    int     i;

    anim = EGB_Component_CreateAnimation(
        "bonus/bomb_add.png", ADD_BOMB_BONUS_ANIMATION_ID, 100, 100, EGB_Animation_Looping
    );

    i = 0;
    while(i < 24) {
        EGB_Animation_AddKeyframe(anim, add_bomb_bonus_anim[i].duration, add_bomb_bonus_anim[i].x, add_bomb_bonus_anim[i].y);
        i++;
    }

    EGB_Component_AddToEntity(bonus, anim);
}


void collect_add_bomb_bonus(EGB_Entity *player, EGB_Entity *bonus)
{
    EGB_Component_Counter *nb_bomb;

    nb_bomb = EGB_FindComponentByName(player, "counter_component");
    nb_bomb->max += 1;

    EGB_Network_DestroyEntity(bonus);
    EGB_Entity_Destroy(bonus);
}