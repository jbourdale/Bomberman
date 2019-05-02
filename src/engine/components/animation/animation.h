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


// animation.c
animation_component_t	*EGB_Component_CreateAnimation(char*, int, int, int, int);
int 					EGB_Component_StartAnimation(entity_t *, int);
int						EGB_Component_StopAnimation(entity_t *, int);

// keyframe.c
int 	EGB_Animation_AddKeyframe(animation_component_t *, int, int, int);
void 	EGB_Keyframe_Set_OnStart(animation_component_t *, int, void (*f)(entity_t *self));
void 	EGB_Keyframe_Set_OnFinish(animation_component_t *, int, void (*f)(entity_t *self));

#endif