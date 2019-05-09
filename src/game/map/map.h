/*
** map.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __MAP_H__
#define __MAP_H__

void create_wall_entity(int x, int y);
void init_background();
void init_map();
void bomb_explose(EGB_Entity *bomb);

#endif
