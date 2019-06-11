/*
** animations.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __BOMB_ANIMATIONS_H__
#define __BOMB_ANIMATIONS_H__

#define BOMB_ANIMATION_ID 	99999
#define EXPLOSION_ANIMATION_ID 	99998

#include "../../game.h"

void create_bomb_animation(EGB_Entity *bomb);
void create_explosion_animation(EGB_Entity *explosion);


#endif