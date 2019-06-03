/*
** map.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __GAME_H__
#define __GAME_H__


typedef struct 	Animation_Description_s 
{
	int 		duration;
	int 		x;
	int 		y;
}				Animation_Description;

#include <pthread.h>

#include "../engine/engine.h"
#include "./player/player.h"
#include "./bomb/bomb.h"
#include "./bomb/animations/animations.h"
#include "./player/animations/animations.h"
#include "./menus/home/home.h"

// server
#include "./server/state/state.h"
#include "./server/server.h"
#include "./server/requests/requests.h"


#endif
