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
