/*
** animate.c for  in /home/dev/C/My_FTL/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "entitys.h"

void enable_entity_animation(entity_t *entity)
{
    log_debug("ENABLE ANIMATION");
    entity->animate = 1;
    entity->last_animation_tick = SDL_GetTicks();
    entity->current_frame = 0;
}

void disable_entity_animation(entity_t *entity)
{
    log_debug("DISABLE ANIMATION");
    entity->animate = 0;
    log_debug("animate : %d", entity->animate);
}

void toggle_entity_animation(entity_t *entity)
{
    if (entity->animate)
        disable_entity_animation(entity);
    else
        enable_entity_animation(entity);
}
