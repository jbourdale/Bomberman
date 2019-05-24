/*
** map.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "../../engine/engine.h"

void bomb_explose(EGB_Entity *bomb) {
    EGB_Component_Position  *position;
    EGB_Component_Collision *collision;
    EGB_Entity              *wall;

    int range[4][2] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };
    int x, y, tmpx, tmpy, i;

    position = EGB_FindComponentByName(
        bomb,
        "position_component"
    );
    if (position == NULL)
        return ;

    x = floor(position->x / 100);
    y = floor(position->y / 100);
    log_debug("x : %d, y : %d", x, y);

    for (i = 0; i < 4; i++) {
        tmpx = x + range[i][0];
        tmpy = y + range[i][1];

        log_debug("tmpx : %d, tmpy : %d", tmpx, tmpy);
        log_debug("looking for wall at : (%d,%d,%d)",
            tmpx * 100,
            tmpy * 100,
            EGB_Position_Top
        );

        wall = EGB_FindEntityByPosition(
            tmpx * 100,
            tmpy * 100,
            EGB_Position_Top
        );
        if (wall != NULL) {
            wall->displayed = 0;
            collision = EGB_FindComponentByName(wall, "collision_component");
            collision->active = 0;
        }
    }
    return ;
}
