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

typedef struct EGB_Animation_Keyframe_s EGB_Animation_Keyframe;

typedef struct 		EGB_Animation_Keyframe_s
{
	// position in spritesheet
	int 			x;
	int 			y;
	// duration in milliseconds
	Uint32 			duration;
	// is this keyframe actually display
	int 			active;
	// next keyframe
	EGB_Animation_Keyframe		*next;

	// events
	void 			(*on_start)(EGB_Entity *self);
	void 			(*on_finish)(EGB_Entity *self);	
}					EGB_Animation_Keyframe;

typedef struct 		EGB_Component_Animation_s
{
	char 			*name;
	int 			running;
	int 			id;
	int 			is_looping;
	int				sprite_width;
	int 			sprite_height;
	EGB_Animation_Keyframe 		*first_keyframe;
	SDL_Texture 	*spritesheet;
    Uint32          last_animation_tick;
} 					EGB_Component_Animation;


// animation.c
EGB_Component_Animation	*EGB_Component_CreateAnimation(char*, int, int, int, int);
int 					EGB_Component_StartAnimation(EGB_Entity *, int);
int						EGB_Component_StopAnimation(EGB_Entity *, int);

// keyframe.c
int 	EGB_Animation_AddKeyframe(EGB_Component_Animation *, int, int, int);
void 	EGB_Keyframe_Set_OnStart(EGB_Component_Animation *, int, void (*f)(EGB_Entity *self));
void 	EGB_Keyframe_Set_OnFinish(EGB_Component_Animation *, int, void (*f)(EGB_Entity *self));

#endif