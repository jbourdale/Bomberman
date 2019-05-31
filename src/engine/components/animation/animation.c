/*
** animation.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "animation.h"

/**
 * @brief      Create a component animation
 * 
 * @note       A entity can have multiple animation. To identify them, you can use
 * the `int id` parameter. When you will start the animation, you will need to pass
 * this `id` to start a specific animation. 
 *
 * @param      spritesheet  The spritesheet resource path
 * @param[in]  id           The animation identifier
 * @param[in]  sprite_w     Width of a single sprite. All your sprites need to have the same width
 * @param[in]  sprite_h     Height of a single sprite. All your sprites need to have the same height
 * @param[in]  is_looping   Indicates if animation must loop after finishing their keyframe
 *
 * @return     the animation component or NULL if something did goes wrong
 */
EGB_Component_Animation 		*EGB_Component_CreateAnimation(
	char 					*spritesheet,
	int 					id,
	int 					sprite_w,
	int 					sprite_h,
	int 					is_looping
)
{
	EGB_Component_Animation 	*comp;
	SDL_Texture 			*texture;

	comp = malloc(sizeof(EGB_Component_Animation));
	comp->name = strdup("animation_component");
	comp->id = id;
	comp->is_looping = is_looping;
	comp->running = 0;
	comp->first_keyframe = NULL;
	comp->sprite_width = sprite_w;
	comp->sprite_height = sprite_h;

	texture = NULL;
    if((texture = (SDL_Texture *)EGB_Get_Resource(spritesheet)) == NULL) {
        log_debug("Can't find %s resource, aborting.", spritesheet);
        return NULL;
    }
    comp->spritesheet = texture;
    return comp;
}

/**
 * @brief      Start the entity animation specified by `animation_id` 
 *
 * @param      entity        The entity
 * @param[in]  animation_id  The animation identifier
 *
 * @return     status   Starting animation status 
 *              <ul>
 *                  <li>0 = Animation successfuly started</li>
 *                  <li>1 = An error occured</li>
 *              </ul>
 */
int 						EGB_Component_StartAnimation(EGB_Entity *entity, int animation_id) {
	EGB_Component_Animation **animation_comps;
	int 					i;

	animation_comps = (EGB_Component_Animation **)EGB_FindComponentsByName(
		entity, "animation_component"
	);
	i = 0;
	while (animation_comps != NULL && animation_comps[i] != NULL) {
		animation_comps[i]->running = 0;
		if (animation_comps[i]->id == animation_id && animation_comps[i]->running == 0) {
			log_debug("STARTING ANIMATION %d, running : %d", animation_id, animation_comps[i]->running);
			animation_comps[i]->last_animation_tick = SDL_GetTicks();
			animation_comps[i]->running = 1;

			if (animation_comps[i]->first_keyframe != NULL) {
				animation_comps[i]->first_keyframe->active = 1;
				if (animation_comps[i]->first_keyframe->on_start != NULL)
					animation_comps[i]->first_keyframe->on_start(entity);
			}
		}
		i++;
	}

	return 1;
}
/**
 * @brief      Stop the entity animation specified by `animation_id` 
 *
 * @param      entity        The entity
 * @param[in]  animation_id  The animation identifier
 *
 * @return     status   Stoping animation status 
 *              <ul>
 *                  <li>0 = Animation successfuly stoped</li>
 *                  <li>1 = An error occured</li>
 *              </ul>
 */
int						EGB_Component_StopAnimation(EGB_Entity *entity, int animation_id) {
	EGB_Component_Animation 	**animation_comps;
	int 					i;

	animation_comps = (EGB_Component_Animation **)EGB_FindComponentsByName(
		entity, "animation_component"
	);
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

int 		EGB_Component_FindRunningAnimation(EGB_Entity *entity) 
{
	EGB_Component_Animation 	**animation_comps;
	int 					i;

	animation_comps = (EGB_Component_Animation **)EGB_FindComponentsByName(
		entity, "animation_component"
	);
	i = 0;
	while (animation_comps != NULL && animation_comps[i] != NULL) {
		if (animation_comps[i]->running == 1) {
			return animation_comps[i]->id;
		}
		i++;
	}
	return -1;
}