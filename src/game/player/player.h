/*
** player.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __PLAYER_H__
#define __PLAYER_H__

void on_player_destroy(EGB_Entity *player);
void init_player();
void bind_my_player();
void player_custom_renderer(SDL_Renderer *renderer, EGB_Entity *entity);
void handle_walk_into_explosion(EGB_Entity *entity);

#endif
