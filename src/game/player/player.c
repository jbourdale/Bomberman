/*
** player.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "../../engine/engine.h"
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
    EGB_Component_Networkable *networkable;

    networkable = EGB_FindComponentByName(entity, "networkable_component");
    log_debug("PLAYER DESTROYED, NETWORK OWNER : %d", networkable->owner);
    EGB_Network_DestroyEntity(entity);
}

/**
 * On player keystroke
 */
void on_player_keystroke(EGB_Entity *entity, SDL_Event e) {
    // EGB_Component_Position    *pos_comp;
    // const Uint8             *key_state = SDL_GetKeyboardState(NULL);

    if (e.type == SDL_KEYUP) {
        EGB_Component_Velocity_SetX(entity, 0);
        EGB_Component_Velocity_SetY(entity, 0);
    }

    if (e.key.keysym.sym == SDLK_LEFT) {
        log_debug("LEFT TRIGGERED, repeat : %d", e.key.repeat);
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            log_debug("START");
            EGB_Component_Velocity_SetX(entity, -4);
            EGB_Component_StartAnimation(entity, LEFT_WALKING_ANIMATION_ID);
        } else if (e.type == SDL_KEYUP) {
            log_debug("STOP");
            EGB_Component_Velocity_SetX(entity, 0);
            EGB_Component_StartAnimation(entity, LEFT_IDLE_ANIMATION_ID);
        }
        EGB_Network_SendEntity(entity);
    }
    else if (e.key.keysym.sym == SDLK_RIGHT) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            EGB_Component_Velocity_SetX(entity, 4);
            EGB_Component_StartAnimation(entity, RIGHT_WALKING_ANIMATION_ID);
        } else if (e.type == SDL_KEYUP) {
            EGB_Component_Velocity_SetX(entity, 0);
            EGB_Component_StartAnimation(entity, RIGHT_IDLE_ANIMATION_ID);
        }
        EGB_Network_SendEntity(entity);
    }
    else if (e.key.keysym.sym == SDLK_UP) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            EGB_Component_Velocity_SetY(entity, -4);
            EGB_Component_StartAnimation(entity, BACK_WALKING_ANIMATION_ID);
        } else if (e.type == SDL_KEYUP) {
            EGB_Component_Velocity_SetY(entity, 0);
            EGB_Component_StartAnimation(entity, BACK_IDLE_ANIMATION_ID);
        }
        EGB_Network_SendEntity(entity);
    }
    else if (e.key.keysym.sym == SDLK_DOWN) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            EGB_Component_Velocity_SetY(entity, 4);
            EGB_Component_StartAnimation(entity, FRONT_WALKING_ANIMATION_ID);
        } else if (e.type == SDL_KEYUP) {
            EGB_Component_Velocity_SetY(entity, 0);
            EGB_Component_StartAnimation(entity, FRONT_IDLE_ANIMATION_ID);
        }
        EGB_Network_SendEntity(entity);
    }
    else if (e.key.keysym.sym == SDLK_SPACE && e.type == SDL_KEYDOWN) {
        place_bomb(entity);
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

void test(char **str)
{
    char *oui;

    oui = strdup("oui");
    *str = oui;
}

void player_custom_renderer(SDL_Renderer *renderer, EGB_Entity *player)
{
    EGB_Entity_DefaultRenderer(renderer, player);
    handle_walk_into_explosion(player);
}

void handle_walk_into_explosion(EGB_Entity *player)
{
    EGB_Component_Position pos;
    EGB_Component_Velocity  *velocity;
    EGB_Component_Position  *position;
    char *collide_with;

    velocity = EGB_FindComponentByName(player, "velocity_component");
    position = EGB_FindComponentByName(player, "position_component");
    if (velocity == NULL || position == NULL) {
        return;
    }

    if (velocity->x > 0) {
        position->x += velocity->x;
        if (EGB_Collide(player, &pos, &collide_with) && strcmp(collide_with, "explosion") == 0)
        {
            EGB_Entity_Destroy(player);
        }
        position->x -= velocity->x;
    }
    else if (velocity->x < 0) {
        position->x -= -velocity->x;
        if (EGB_Collide(player, &pos, &collide_with) && strcmp(collide_with, "explosion") == 0)
        {
            EGB_Entity_Destroy(player);
        }
        position->x += -velocity->x;
    }

    if (velocity->y > 0) {
        position->y -= velocity->y;
        if (EGB_Collide(player, &pos, &collide_with) && strcmp(collide_with, "explosion") == 0)
        {
            EGB_Entity_Destroy(player);
        }
        position->y += velocity->y;
    }
    else if (velocity->y < 0) {
        position->y += -velocity->y;
        if (EGB_Collide(player, &pos, &collide_with) && strcmp(collide_with, "explosion") == 0)
        {
            EGB_Entity_Destroy(player);
        }
        position->y -= -velocity->y;
    }
}