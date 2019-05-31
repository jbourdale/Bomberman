/*
** idle.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "animations.h"

char 					*get_player_spritesheet(EGB_Entity *player) 
{
	EGB_Component_Id 	*id_comp;
	char 				*spritesheet;

	id_comp = EGB_FindComponentByName(player, "id_component");
    if (id_comp == NULL) {
        log_debug("No ID found on player");
        return NULL;
    }

	spritesheet = strdup("player/blue.png");
    switch(id_comp->id) {
        case 1:
            spritesheet = strdup("player/yellow.png");
            break;
        case 2:
            spritesheet = strdup("player/green.png");
            break;
        case 3:
            spritesheet = strdup("player/red.png");
            break;
    }

    return spritesheet;
}

void 	add_animation_keyframes(EGB_Component_Animation *comp, Animation_Description *anim, int size)
{
	int 	i;

	i = 0;
	while(i < size) {
		EGB_Animation_AddKeyframe(comp, anim[i].duration, anim[i].x, anim[i].y);
		i++;
	}
}