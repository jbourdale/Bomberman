/*
** entity.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entities.h"

/**
 * @brief      Default renderer for entities
 *
 * @note       You can override this renderer with your custom one as follow
 * @code
 *      EGB_Entity *entity = EGB_Entity_Create("whatever");
 *      entity->render = my_custom_render_function
 * @endcode
 * @param      renderer  SDL_Renderer the current renderer
 * @param      entity    The entity to render
 */
void                        EGB_Entity_DefaultRenderer(SDL_Renderer *renderer, EGB_Entity *entity)
{
    EGB_Component_Animation   **animation_comps;
    EGB_Component_Position    *pos_comp;

    if (!entity->displayed) {
        log_debug("entity %s displayed : %d", entity->name, entity->displayed);
        return ;
    }

    pos_comp = (EGB_Component_Position*)EGB_FindComponentByName(entity, "position_component");
    if (pos_comp == NULL) {
        log_debug("position_component not founded in entity");
        return ;
    }

    animation_comps = (EGB_Component_Animation **)EGB_FindComponentsByName(
        entity,
        "animation_component"
    );
    if (animation_comps == NULL) {
        EGB_Render_EntityTexture(renderer, entity, pos_comp);
    } else {
        EGB_Render_EntityAnimation(renderer, entity, animation_comps, pos_comp);
    }
}


/**
 * @brief      Render all entities. Called on each frame rendering
 */
void                        EGB_Render_Entities()
{
    SDL_Renderer            *renderer;
    EGB_Entity_Manager        *entities_manager;
    EGB_Entity_Manager_Element *manager_iterator;
    EGB_Entity                *entity;
    int                         i;

    renderer = EGB_SDL_GetCurrentRenderer();
    SDL_RenderClear(renderer);
    entities_manager = EGB_Observable_Position(EGB_Manager_Retrieve);
    manager_iterator = entities_manager->first;
    i = 0;
    while (manager_iterator != NULL)
    {
        entity = manager_iterator->entity;
        entity->render(renderer, entity);
        manager_iterator = manager_iterator->next;
        i++;
    }
    log_debug("RENDERED %d ENTITIES", i);
    SDL_RenderPresent(renderer);
}

/**
 * @brief      Default renderer for entity animation
 *
 * @note       If you override the default entity renderer,
 * you still can use this one to render your animation
 *
 * @param      renderer  The SDL renderer
 * @param      entity    The entity to renderer
 * @param      comps     All the animation components from the entity
 * @param      pos_comp  The position component of the entity
 *
 * @todo       Split this function, refactor params
 */
void                        EGB_Render_EntityAnimation(
    SDL_Renderer            *renderer,
    EGB_Entity                *entity,
    EGB_Component_Animation   **comps,
    EGB_Component_Position    *pos_comp
) {
    SDL_Rect                sprite_rect, position_on_screen;
    EGB_Component_Animation   **comps_iterator;
    EGB_Animation_Keyframe              *keyfame_iterator;
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

    EGB_Component_PositionToRect(pos_comp, &position_on_screen);
    sprite_rect.x = keyfame_iterator->x * comps_iterator[i]->sprite_width;
    sprite_rect.y = keyfame_iterator->y * comps_iterator[i]->sprite_height;
    sprite_rect.w = comps_iterator[i]->sprite_width;
    sprite_rect.h = comps_iterator[i]->sprite_height;
    SDL_RenderCopy(renderer, comps_iterator[i]->spritesheet, &sprite_rect, &position_on_screen);
}

/**
 * @brief      Render an entity texture component
 *
 * @note       If you override the default entity renderer,
 * you still can use this one to render your animation
 *
 * @param      renderer  The renderer
 * @param      entity    The entity
 * @param      pos_comp  The position component
 */
void                        EGB_Render_EntityTexture(
    SDL_Renderer            *renderer,
    EGB_Entity                *entity,
    EGB_Component_Position    *pos_comp
)
{
    EGB_Component_Texture      *comp;
    SDL_Rect                position_on_screen;

    log_debug("render texture for entity (%s)", entity->name);

    comp = (EGB_Component_Texture*)EGB_FindComponentByName(entity, "texture_component");
    if (comp == NULL) {
        log_debug("no texture_component founded");
        return ;
    }

    EGB_Component_PositionToRect(pos_comp, &position_on_screen);
    log_debug("comp->texture(%p) == NULL : %d", comp->texture, comp->texture == NULL);
    log_debug("Render texture (%p) at (%d, %d, %d, %d)", comp->texture,
        position_on_screen.x,
        position_on_screen.y,
        position_on_screen.w,
        position_on_screen.h
    );
    SDL_RenderCopy(renderer, comp->texture, NULL, &position_on_screen);
}
