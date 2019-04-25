/*
** animation.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "animation.h"

animation_component_t 		*create_animation_component(
	char 					*spritesheet,
	int 					id,
	int 					sprite_w,
	int 					sprite_h,
	int 					is_looping
)
{
	SDL_Renderer			*renderer;
	animation_component_t 	*comp;
	SDL_Texture 			*texture;

	renderer = get_current_renderer();

	comp = malloc(sizeof(animation_component_t));
	comp->name = strdup("animation_component");
	comp->id = id;
	comp->is_looping = is_looping;
	comp->running = 0;
	comp->first_keyframe = NULL;
	comp->sprite_width = sprite_w;
	comp->sprite_height = sprite_h;

	texture = NULL;
    if(create_sprite(renderer, spritesheet, &texture)) {
        log_debug("A NULL sprite have been created, aborting.");
        return NULL;
    }
    comp->spritesheet = texture;
    return comp;
}

int 						start_entity_animation(entity_t *entity, int animation_id) {
	animation_component_t 	**animation_comps;
	int 					i;

	animation_comps = (animation_component_t **)find_components_by_name(entity, "animation_component");
	i = 0;
	while (animation_comps != NULL && animation_comps[i] != NULL) {
		if (animation_comps[i]->id == animation_id) {
			animation_comps[i]->last_animation_tick = SDL_GetTicks();
			animation_comps[i]->running = 1;

			if (animation_comps[i]->first_keyframe != NULL) {
				animation_comps[i]->first_keyframe->active = 1;
				if (animation_comps[i]->first_keyframe->on_start != NULL)
					animation_comps[i]->first_keyframe->on_start(entity);
			}
			return 0;
		}
		i++;
	}

	return 1;
}

int						stop_entity_animation(entity_t *entity, int animation_id) {
	animation_component_t 	**animation_comps;
	int 					i;

	animation_comps = (animation_component_t **)find_components_by_name(entity, "animation_component");
	i = 0;
	while (animation_comps != NULL && animation_comps[i] != NULL) {
		if (animation_comps[i]->id == animation_id) {
			animation_comps[i]->running = 0;
			return 0;
		}
		i++;
	}

	return 1;
}
