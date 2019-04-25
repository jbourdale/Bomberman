/*
** entity.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entitys.h"

void                        _base_entity_render(SDL_Renderer *renderer, entity_t *entity)
{
    animation_component_t   **animation_comps;
    position_component_t    *pos_comp;

    if (!entity->displayed)
        return ;

    pos_comp = (position_component_t*)find_component_by_name(entity, "position_component");
    if (pos_comp == NULL)
        return ;

    animation_comps = (animation_component_t **)find_components_by_name(
        entity,
        "animation_component"
    );
    if (animation_comps == NULL) {
        render_entity_texture(renderer, entity, pos_comp);
    } else {
        render_entity_animation(renderer, entity, animation_comps, pos_comp);
    }
}


void                render_entitys()
{
    SDL_Renderer    *renderer;
    entity_t        **current_entitys;
    int             i, nb_entity;

    renderer = get_current_renderer();
    current_entitys = entitys_manager(NULL);
    nb_entity = 0;
    while(current_entitys[nb_entity] != NULL)
        nb_entity++;
    i = 0;
    while (current_entitys[i] != NULL)
    {
        current_entitys[i]->render(renderer, current_entitys[i]);
        i++;
    }
}

// TODO : Cut this function in smaller ones
void                        render_entity_animation(
    SDL_Renderer            *renderer,
    entity_t                *entity,
    animation_component_t   **comps,
    position_component_t    *pos_comp
) {
    SDL_Rect                sprite_rect, position_on_screen;
    animation_component_t   **comps_iterator;
    keyframe_t              *keyfame_iterator;
    int                     i, nb_animation;


    comps_iterator = comps;
    nb_animation = 0;
    while (comps_iterator[++nb_animation] != NULL);

    // Finding the current running animation
    i = 0;
    while (i < nb_animation && comps_iterator[i]->running == 0) {
        i++;
    }
    if (i == nb_animation) {
        return;
    }

    // finding the current active keyframe
    keyfame_iterator = comps_iterator[i]->first_keyframe;
    if (keyfame_iterator == NULL) {
        log_warn("animation is running but do not have any keyframe");
        return;
    }
    while (keyfame_iterator != NULL && !keyfame_iterator->active)
        keyfame_iterator = keyfame_iterator->next;
    if (keyfame_iterator == NULL) {
        log_warn("annimation is running but no keyframe is active");
        return ;
    }

    // If the keyframe duration is over, roll to the next one
    // If the animation have a next keyframe, go to it
    // if it doesn't but the animation is looping, go back to the first one
    if (SDL_GetTicks() - comps_iterator[i]->last_animation_tick > keyfame_iterator->duration) {
        comps_iterator[i]->last_animation_tick = SDL_GetTicks();

        keyfame_iterator->active = 0;
        if (keyfame_iterator->on_finish != NULL)
            keyfame_iterator->on_finish(entity);

        if (keyfame_iterator->next != NULL) {
            keyfame_iterator->next->active = 1;
            if (keyfame_iterator->next->on_start != NULL)
                keyfame_iterator->next->on_start(entity);
        }
        else if (comps_iterator[i]->is_looping) {
            comps_iterator[i]->first_keyframe->active = 1;
        } else {
            comps_iterator[i]->running = 0;
        }
    }

    position_component_to_rect(pos_comp, &position_on_screen);
    sprite_rect.x = keyfame_iterator->x * comps_iterator[i]->sprite_width;
    sprite_rect.y = keyfame_iterator->y * comps_iterator[i]->sprite_height;
    sprite_rect.w = comps_iterator[i]->sprite_width;
    sprite_rect.h = comps_iterator[i]->sprite_height;
    SDL_RenderCopy(renderer, comps_iterator[i]->spritesheet, &sprite_rect, &position_on_screen);
}

void                        render_entity_texture(
    SDL_Renderer            *renderer,
    entity_t                *entity,
    position_component_t    *pos_comp
)
{
    texture_component_t      *comp;
    SDL_Rect                position_on_screen;

    comp = (texture_component_t*)find_component_by_name(entity, "texture_component");
    if (comp == NULL)
        return ;

    position_component_to_rect(pos_comp, &position_on_screen);
    SDL_RenderCopy(renderer, comp->texture, NULL, &position_on_screen);
}
