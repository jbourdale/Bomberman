/*
** init.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "../../../engine/engine.h"
#include "state.h"
#include "../requests/requests.h"

int base_map[11][11] = {
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
    {3, 0, 2, 1, 2, 1, 2, 1, 2, 0, 3},
    {3, 0, 1, 1, 1, 1, 1, 1, 1, 0, 3},
    {3, 0, 2, 1, 2, 1, 2, 1, 2, 0, 3},
    {3, 0, 1, 1, 1, 1, 1, 1, 1, 0, 3},
    {3, 0, 2, 1, 2, 1, 2, 1, 2, 0, 3},
    {3, 0, 1, 1, 1, 1, 1, 1, 1, 0, 3},
    {3, 0, 2, 1, 2, 1, 2, 1, 2, 0, 3},
    {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}
};

EGB_Entity                      *init_new_player(int id, struct sockaddr_in client_addr) {
    EGB_Entity                 *player;
    EGB_Component_Position     *pos_comp;
    EGB_Component_Id           *id_comp;
    EGB_Component_Collision    *collision_comp;
    EGB_Component_Networkable  *networkable_comp;
    EGB_Component_Velocity     *velocity_comp;
    char                       *addr;
    int                        x, y;

    x = 100;
    y = 100;
    switch(id) {
        case 1:
            x = 100;
            y = 900;
            break;
        case 2:
            x = 900;
            y = 100;
            break;
        case 3:
            x = 900;
            y = 900;
            break;
        default:
            break;
    }

    player = EGBS_Entity_Create("player");
    log_debug("[SERVER SIDE] entity player : %p at (%d,%d)", player, x, y);
    pos_comp = EGB_Component_CreatePosition(x + 360, y + 10, EGB_Position_Classic, 80, 80);

    collision_comp = EGB_Component_CreateCollision(1);
    id_comp = EGB_Component_CreateId(id);
    velocity_comp = EGB_Component_CreateVelocity(0, 0);
    networkable_comp = EGB_Component_CreateNetworkable();
    asprintf(&addr, "%s:%d", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    networkable_comp->owner_addr = addr;

    EGB_Component_AddToEntity(player, pos_comp);
    EGB_Component_AddToEntity(player, id_comp);
    EGB_Component_AddToEntity(player, velocity_comp);
    EGB_Component_AddToEntity(player, collision_comp);
    EGB_Component_AddToEntity(player, networkable_comp);
    return player;
}

void init_background() {
    EGB_Entity *bg;
    EGB_Component_Texture *texture_comp;
    EGB_Component_Position *pos_comp;
    EGB_Component_Networkable *network_comp;

    bg = EGBS_Entity_Create("background");
    pos_comp = EGB_Component_CreatePosition(0, 0, EGB_Position_Background, 1920, 1080);
    network_comp = EGB_Component_CreateNetworkable();
    texture_comp = EGB_Component_CreateTexture("background.png");
    EGB_Component_AddToEntity(bg, (void *)pos_comp);
    EGB_Component_AddToEntity(bg, (void *)texture_comp);
    EGB_Component_AddToEntity(bg, (void *)network_comp);
}

void init_map() {
    int i, j;

    for(i = 0; i < 11; i++) {
        for(j = 0; j < 11; j++) {
            switch(base_map[i][j]) {
                case 0:
                    create_floor(i, j);
                    break;
                case 1:
                    create_wall_entity(i, j);
                    break;
                case 2:
                    create_indestructible_wall(i, j);
                    break;
                case 3:
                    create_outer_wall(i, j);
                    break;
                default:
                    break;
            }
        }
    }
}

void init_game() {
    //init_background();
    init_map();
}


void check_game_over(int sock) 
{
    EGB_Entity **players;
    int i;

    players = EGBS_Entity_FindByName("player");
    if (players == NULL || *players == NULL) {
        broadcast_event_to_players(sock, "END");
        return ;
    }

    i = 0;
    while (*players != NULL)
    {
        i++;
        players++;
    }

    if (i < 1)
    {
        broadcast_event_to_players(sock, "END");
    }
}