/*
** player.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "../../engine/engine.h"
#include "../map/map.h"
#include "../server/server.h"

/**
 * PLAYER HANDLER CLICK
 */
void on_player_click(EGB_Entity *entity, SDL_Event e)
{
    log_debug("on click on : %s", entity->name);
    log_debug("e : %p", &e);
    EGB_Entity_Destroy(entity);
}

void player_on_destroy(EGB_Entity *entity) {
    EGB_Network_DestroyEntity(entity);
}

/**
 * On player keystroke
 */
void on_player_keystroke(EGB_Entity *entity) {
    EGB_Component_Position    *pos_comp;
    const Uint8             *key_state = SDL_GetKeyboardState(NULL);

    key_state = SDL_GetKeyboardState(NULL);
    pos_comp = (EGB_Component_Position*)EGB_FindComponentByName(entity, "position_component");
    if(key_state[SDL_SCANCODE_LEFT]) {
        EGB_Position_Move_Left(entity, 10);
        EGB_Network_SendEntity(entity);
    }
    if (key_state[SDL_SCANCODE_RIGHT]) {
        EGB_Position_Move_Right(entity, 10);
        EGB_Network_SendEntity(entity);
    }
    if (key_state[SDL_SCANCODE_UP]) {
        EGB_Position_Move_Up(entity, 10);
        EGB_Network_SendEntity(entity);
    }
    if (key_state[SDL_SCANCODE_DOWN]) {
        EGB_Position_Move_Down(entity, 10);
        EGB_Network_SendEntity(entity);
    }
    if (key_state[SDL_SCANCODE_S]) {
        start_server_thread();
    }
    if (key_state[SDL_SCANCODE_SPACE])
    {
        EGB_Entity *player = EGB_Entity_Create("bomb");
        EGB_Component_Position *pos_comp2 = EGB_Component_CreatePosition(
            pos_comp->x, pos_comp->y, EGB_Position_Background, 75, 75);
        EGB_Component_Animation *animation_comp = EGB_Component_CreateAnimation(
            "bomb.png", 0, 24, 24, 0
        );
        EGB_Animation_AddKeyframe(animation_comp, 400, 0, 0);
        EGB_Animation_AddKeyframe(animation_comp, 400, 1, 0);
        EGB_Animation_AddKeyframe(animation_comp, 400, 2, 0);
        EGB_Animation_AddKeyframe(animation_comp, 200, 3, 0);
        EGB_Animation_AddKeyframe(animation_comp, 200, 0, 4);
        EGB_Animation_AddKeyframe(animation_comp, 200, 0, 3);
        EGB_Animation_AddKeyframe(animation_comp, 200, 0, 2);
        int keyframe_id = EGB_Animation_AddKeyframe(animation_comp, 200, 0, 1);
        EGB_Keyframe_Set_OnFinish(animation_comp, keyframe_id, bomb_explose);
        EGB_Component_AddToEntity(player, (void *)pos_comp2);
        EGB_Component_AddToEntity(player, (void *)animation_comp);
        EGB_Component_StartAnimation(player, 0);
    }
}


void 						    bind_my_player()
{
	EGB_Entity 				    **players;
    int                         i;
    EGB_Component_Networkable   *network_comp;
	EGB_Component_Event 	    *keystroke_event, *click_event;

	players = EGB_Entity_FindByName("player");
    if (players == NULL)
        return ;

    i = 0;
    while (players[i] != NULL) {
        network_comp = EGB_FindComponentByName(players[i], "networkable_component");
        if (network_comp == NULL)
            continue;
        if (network_comp->owner)
            break;
        i++;
    }
    log_debug("[CLIENT SIDE] BIND MY PLAYER > MY PLAYER : %d", i);

    players[i]->on_destroy = player_on_destroy;
    keystroke_event = EGB_Component_CreateEventKeyStroke(on_player_keystroke);
    click_event = EGB_Component_CreateEventClick(on_player_click);

    EGB_Component_AddToEntity(players[i], keystroke_event);
    EGB_Component_AddToEntity(players[i], click_event);
}
