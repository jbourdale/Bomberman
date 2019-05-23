/*
** init.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "../../../engine/engine.h"
#include "state.h"

int base_map[11][11] = {
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    {3, 0, 0, 1, 1, 1, 1, 1, 0, 0, 3},
    {3, 0, 2, 1, 2, 1, 2, 1, 2, 0, 3},
    {3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {3, 1, 2, 1, 2, 1, 2, 1, 2, 1, 3},
    {3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {3, 1, 2, 1, 2, 1, 2, 1, 2, 1, 3},
    {3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {3, 0, 2, 1, 2, 1, 2, 1, 2, 0, 3},
    {3, 0, 0, 1, 1, 1, 1, 1, 0, 0, 3},
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}
};

EGB_Entity *init_new_player(int id) {
    EGB_Entity                 *player;
    EGB_Component_Position     *pos_comp;
    EGB_Component_Texture      *texture_comp;
    EGB_Component_Collision    *collision_comp;
    EGB_Component_Networkable  *networkable_comp;
    int                        x, y;

    x = 100;
    y = 100;
    switch(id) {
        case 1:
            x = 900;
            y = 100;
            break;
        case 2:
            x = 100;
            y = 900;
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
    pos_comp = EGB_Component_CreatePosition(x, y, EGB_Position_Classic, 100, 100);
    texture_comp = EGB_Component_CreateTexture("Mario.png");
    collision_comp = EGB_Component_CreateCollision(1);
    networkable_comp = EGB_Component_CreateNetworkable();

    EGB_Component_AddToEntity(player, pos_comp);
    EGB_Component_AddToEntity(player, texture_comp);
    EGB_Component_AddToEntity(player, collision_comp);
    EGB_Component_AddToEntity(player, networkable_comp);
    return player;
}

void init_map() {
    int i, j;

    for(i = 0; i < 11; i++) {
        for(j = 0; j < 11; j++) {
            switch(base_map[i][j]) {
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
    init_map();
}
