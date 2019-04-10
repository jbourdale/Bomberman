/*
** animate.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "entitys.h"

void enable_entity_animation(entity_t *entity)
{
    entity->animate = 1;
    entity->last_animation_tick = SDL_GetTicks();
    entity->current_frame = 0;
}

void disable_entity_animation(entity_t *entity)
{
    entity->animate = 0;
}

void toggle_entity_animation(entity_t *entity)
{
    if (entity->animate)
        disable_entity_animation(entity);
    else
        enable_entity_animation(entity);
}
