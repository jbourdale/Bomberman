/*
** bonus.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __BONUS_H__
#define __BONUS_H__

#include "../game.h"

#define RANGE_BONUS_ANIMATION_ID 12345

void create_range_bonus_animation(EGB_Entity *bonus);
void collect_range_bonus(EGB_Entity *player, EGB_Entity *bonus);

#endif