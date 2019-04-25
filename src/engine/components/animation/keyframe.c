/*
** keyframe.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "animation.h"

void 						add_keyframe_on_start_event(
	animation_component_t *animation,
	int keyframe_id,
	void (*f)(entity_t *)
) {
	keyframe_t 				*keyframe_iterator;
	int 					i;

	if (animation != NULL) {
		i = 0;
		keyframe_iterator = animation->first_keyframe;
		while(keyframe_iterator != NULL && keyframe_iterator->next != NULL && i != keyframe_id) {
			i++;
			keyframe_iterator = keyframe_iterator->next;
		}
		if (keyframe_iterator != NULL)
		keyframe_iterator->on_start = f;
	} else
		log_warn("add_keyframe_on_start_event > animation provided is NULL");
}

void 						add_keyframe_on_finish_event(
	animation_component_t *animation,
	int keyframe_id,
	void (*f)(entity_t *)
) {
	keyframe_t 				*keyframe_iterator;
	int 					i;

	log_debug("add_keyframe_on_finish_event on %d", keyframe_id);

	if (animation != NULL) {
		i = 0;
		keyframe_iterator = animation->first_keyframe;
		while(keyframe_iterator != NULL && keyframe_iterator->next != NULL && i != keyframe_id) {
			i++;
			keyframe_iterator = keyframe_iterator->next;
		}
		log_debug("ADDING ON FINISH EVENT ON %p KEYFRAME", keyframe_iterator);
		if (keyframe_iterator != NULL)
			keyframe_iterator->on_finish = f;
	} else
		log_warn("add_keyframe_on_finish_event > animation provided is NULL");
}

int 			add_animation_keyframe(animation_component_t *animation, int duration, int x, int y)
{
	keyframe_t 	*keyframe_iterator;
	keyframe_t  *keyframe;

	if (animation == NULL) {
		log_debug("null animation provided");
		return 1;
	}

    keyframe = malloc(sizeof(keyframe_t));
	keyframe->duration = duration;
	keyframe->active = 0;
	keyframe->on_finish = NULL;
	keyframe->on_start = NULL;
	keyframe->x = x;
	keyframe->y = y;
	keyframe->next = NULL;

	keyframe_iterator = animation->first_keyframe;
	// log_debug("keyframe_iterator == NULL : %d", keyframe_iterator == NULL);
	if (keyframe_iterator == NULL) {
		keyframe->active = 1;
		animation->first_keyframe = keyframe;
		log_debug("adding keyframe as first > first_keyframe == %p", animation->first_keyframe);
		return 0;
	}

	int i = 0;
    while(keyframe_iterator != NULL && keyframe_iterator->next != NULL) {
        keyframe_iterator = keyframe_iterator->next;
        i++;
    }
    log_debug("ADDING THE %d EME KEYFRAME : %p", i + 1, keyframe);
    keyframe_iterator->next = keyframe;
    log_debug("keyframe->next == NULL : %d", keyframe_iterator->next == NULL);
	return i;
}
