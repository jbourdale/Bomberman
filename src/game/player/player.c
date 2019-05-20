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
 * MARIO HANDLER CLICK
 */
void on_mario_click(EGB_Entity *entity, SDL_Event e)
{
    log_debug("on click on : %s", entity->name);
    log_debug("e : %p", &e);
    EGB_Entity_Destroy(entity);
}

void player_on_destroy(EGB_Entity *entity) {
    EGB_Network_DestroyEntity(entity);
}

void on_explosion(EGB_Entity *entity) {
    log_debug("BOMB EXPLOSED : %s", entity->name);
}
void on_start(EGB_Entity *entity) {
    log_debug("BOMB PLACED : %s", entity->name);
}

/**
 * On mario keystroke
 */
void on_mario_keystroke(EGB_Entity *entity) {
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
        int start_keyframe = EGB_Animation_AddKeyframe(animation_comp, 400, 0, 0);
        EGB_Keyframe_Set_OnStart(animation_comp, start_keyframe, on_start);
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


void 						init_player()
{
	EGB_Entity 				   *mario;
	EGB_Component_Position     *pos_comp;
	EGB_Component_Texture 	   *texture_comp;
	EGB_Component_Event 	   *keystroke_event, *click_event;
    EGB_Component_Collision    *collision_comp;
    EGB_Component_Networkable  *networkable_comp;

	mario = EGB_Entity_Create("player");
    mario->on_destroy = player_on_destroy;
    log_debug("entity mario : %p", mario);
    keystroke_event = EGB_Component_CreateEventKeyStroke(on_mario_keystroke);
    click_event = EGB_Component_CreateEventClick(on_mario_click);
    pos_comp = EGB_Component_CreatePosition(125, 125, EGB_Position_Classic, 50, 50);
    texture_comp = EGB_Component_CreateTexture("Mario.png");
    texture_comp = EGB_Component_CreateTexture("Mario.png");
    collision_comp = EGB_Component_CreateCollision(1);
    networkable_comp = EGB_Component_CreateNetworkable();

    EGB_Component_AddToEntity(mario, keystroke_event);
    EGB_Component_AddToEntity(mario, click_event);
    EGB_Component_AddToEntity(mario, pos_comp);
    EGB_Component_AddToEntity(mario, texture_comp);
    EGB_Component_AddToEntity(mario, collision_comp);
    EGB_Component_AddToEntity(mario, networkable_comp);
}
