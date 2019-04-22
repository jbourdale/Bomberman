/*
** animation.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "../../engine.h"

typedef struct keyframe_s keyframe_t;

typedef struct 		keyframe_s
{
	// position in spritesheet
	int 			x;
	int 			y;
	// duration in milliseconds
	Uint32 			duration;
	// is this keyframe actually display
	int 			active;
	// next keyframe
	keyframe_t		*next;

	// events
	void 			(*on_start)(entity_t *self);
	void 			(*on_finish)(entity_t *self);	
}					keyframe_t;

typedef struct 		animation_component_s
{
	char 			*name;
	int 			running;
	int 			id;
	int 			is_looping;
	int				sprite_width;
	int 			sprite_height;
	keyframe_t 		*first_keyframe;
	SDL_Texture 	*spritesheet;
    Uint32          last_animation_tick;
} 					animation_component_t;

animation_component_t 		*create_animation_component(
	char 					*spritesheet, 
	int 					id,
	int 					sprite_w,
	int 					sprite_h,
	int 					is_looping
);
int add_animation_keyframe(animation_component_t *animation, int duration, int x, int y);
int start_entity_animation(entity_t *entity, int animation_id);
int	stop_entity_animation(entity_t *entity, int animation_id);
void add_keyframe_on_start_event(animation_component_t *animation, int keyframe_id, void (*f)(entity_t *self));
void add_keyframe_on_finish_event(animation_component_t *animation, int keyframe_id, void (*f)(entity_t *self));
#endif