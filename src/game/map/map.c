/*
** map.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "../../engine/engine.h"

int map[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void create_wall_entity(int x, int y)
{
    EGB_Entity *wall;
    EGB_Component_Texture *texture_comp;
    EGB_Component_Position *pos_comp;
    EGB_Component_Collision *collision_comp;

    wall = EGB_Entity_Create("wall");
    texture_comp = EGB_Component_CreateTexture("wall.png");
    log_debug("Creating wall at (%d, %d, %d)", x*100, y*100, EGB_Position_Top);
    pos_comp = EGB_Component_CreatePosition(x * 100, y * 100, EGB_Position_Top, 100, 100);
    collision_comp = EGB_Component_CreateCollision(1);
    EGB_Component_AddToEntity(wall, (void *)texture_comp);
    EGB_Component_AddToEntity(wall, (void *)pos_comp);
    EGB_Component_AddToEntity(wall, (void *)collision_comp);
}

void init_background() {
    EGB_Entity *bg;
    EGB_Component_Texture *texture_comp;
    EGB_Component_Position *pos_comp;

    bg = EGB_Entity_Create("background");
    pos_comp = EGB_Component_CreatePosition(0, 0, EGB_Position_Background, 1920, 1080);
    texture_comp = EGB_Component_CreateTexture("background.png");
    EGB_Component_AddToEntity(bg, (void *)pos_comp);
    EGB_Component_AddToEntity(bg, (void *)texture_comp);
}

void init_map() {
    int i, j;

    init_background();

    for(i = 0; i < 10; i++) {
        for(j = 0; j < 10; j++) {
            switch(map[i][j]) {
                case 1:
                    create_wall_entity(i, j);
                    break;
                default:
                    break;
            }
        }
    }
}

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
