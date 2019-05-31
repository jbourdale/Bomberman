/*
** animations.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __GAME_PLAYER_ANIMATIONS_H_
#define __GAME_PLAYER_ANIMATIONS_H_

#include "../../game.h"

#define BACK_DYING_ANIMATION_ID 	0
#define BACK_IDLE_ANIMATION_ID  	1
#define BACK_WALKING_ANIMATION_ID 	2
#define FRONT_DYING_ANIMATION_ID 	3
#define FRONT_IDLE_ANIMATION_ID  	4
#define FRONT_WALKING_ANIMATION_ID 	5
#define LEFT_DYING_ANIMATION_ID 	6
#define LEFT_IDLE_ANIMATION_ID  	7
#define LEFT_WALKING_ANIMATION_ID 	8
#define RIGHT_DYING_ANIMATION_ID 	9
#define RIGHT_IDLE_ANIMATION_ID  	10
#define RIGHT_WALKING_ANIMATION_ID 	11

char *get_player_spritesheet(EGB_Entity *player);
void add_animation_keyframes(EGB_Component_Animation *comp, Animation_Description *anim, int size);

void add_idle_animations(EGB_Entity *player);
void add_walking_animations(EGB_Entity *player);

#endif