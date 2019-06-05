/*
** bomb.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "../requests/requests.h"
#include "state.h"

void handle_bomb_explosion(int sock, EGB_Entity *bomb)
{
    EGB_Component_Position  *position;
	EGB_Component_Range  *range_comp;

    int area[5][2] = {
        {0, 0},
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };
    int x, y, tmpx, tmpy, i, j;

    position = EGB_FindComponentByName(bomb,"position_component");
    range_comp = EGB_FindComponentByName(bomb, "range_component");
    if (position == NULL || range_comp == NULL)
        return ;

    destroy_entity(sock, bomb);

    x = floor((position->x - 350)/ 100);
    y = floor(position->y / 100);

    for (i = 0; i < 5; i++) {
        for (j = 1; j <= range_comp->range; j++) {
            tmpx = x + (area[i][0] * j);
            tmpy = y + (area[i][1] * j);

            if (tmpx < 0 || tmpx > 10 || tmpy < 0 || tmpy > 10)
                continue;

            log_debug("tmpx : %d, tmpy : %d", tmpx, tmpy);
            create_explosion(sock, tmpx, tmpy);
            destroy_players(sock, tmpx, tmpy);
            if (destroy_wall(sock, tmpx, tmpy)) {
                break;
            }
        }
    }
    check_game_over(sock);
    return ;
}

int destroy_wall(int sock, int x, int y)
{
    EGB_Entity *wall, *floor;
    char    *encoded_floor;

    wall = EGBS_FindEntityByPosition(
            (x * 100) + 350,
            y * 100,
            EGB_Position_Top
        );

    if (wall == NULL) 
        return 0;
    if (strcmp(wall->name, "outer_wall") == 0 ||
        strcmp(wall->name, "indestructible_wall") == 0   
    )
        return 1;

    if (strcmp(wall->name, "bomb") == 0) {
        log_debug("A ANOTHER BOMB HAVE BEEN DESTROYED");
        handle_bomb_explosion(sock, wall);
    }

    floor = create_floor(x, y);
    encoded_floor = EGB_Serializer_EncodeEntity(floor);
    broadcast_to_players(sock, encoded_floor, NULL);
    if (strcmp(wall->name, "wall") == 0)
        generate_bonus(sock, x, y);

    destroy_entity(sock, wall);
    return 1;
}

void destroy_players(int sock, int x, int y)
{
    EGB_Entity  **players;
    EGB_Component_Position *pos;
    int         player_x, player_y;

    players = EGBS_Entity_FindByName("player");
    if (players == NULL)
        return ; // END GAME ?

    while(*players != NULL)
    {
        pos = EGB_FindComponentByName(*players, "position_component");
        if (pos == NULL)
            continue;

        player_x = floor(((pos->x + pos->width / 2) - 350) / 100);
        player_y = floor((pos->y + pos->height / 2) / 100);

        if (player_x == x && player_y == y)
        {
            destroy_entity(sock, *players);
        }
        players++;
    }
}

void create_explosion(int sock, int x, int y)
{
    char *encoded_explosion;
    EGB_Entity *explosion, *wall;
    EGB_Component_Position *position;
    EGB_Component_Collision *collision;
    EGB_Component_Networkable *networkable;

    wall = EGBS_FindEntityByPosition(
            (x * 100) + 350,
            y * 100,
            EGB_Position_Top
    );
    if (wall != NULL && ( 
        strcmp(wall->name, "indestructible_wall") == 0 || 
        strcmp(wall->name, "outer_wall") == 0
    ))
        return ;

    explosion = EGBS_Entity_Create("explosion");
    position = EGB_Component_CreatePosition(
        x * 100 + 350,
        y * 100,
        EGB_Position_AlwaysOnTop,
        100,
        100
    );
    collision = EGB_Component_CreateCollision(1);
    networkable = EGB_Component_CreateNetworkable();

    EGB_Component_AddToEntity(explosion, position);
    EGB_Component_AddToEntity(explosion, collision);
    EGB_Component_AddToEntity(explosion, networkable);

    encoded_explosion = EGB_Serializer_EncodeEntity(explosion);
    broadcast_to_players(sock, encoded_explosion, NULL);
}
