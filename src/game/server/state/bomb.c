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

    int range[4][2] = {
        {0, 0},
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

    x = floor((position->x - 350)/ 100);
    y = floor(position->y / 100);
    log_debug("BOMB POSITION (%d, %d) THAT MEAN IT'S ON (%d, %d)", position->x, position->y, x, y);
    log_debug("x : %d, y : %d", x, y);

    for (i = 0; i < 4; i++) {
        tmpx = x + range[i][0];
        tmpy = y + range[i][1];

        log_debug("tmpx : %d, tmpy : %d", tmpx, tmpy);
        create_explosion(sock, tmpx, tmpy);
        destroy_wall(sock, tmpx, tmpy);
        destroy_players(sock, tmpx, tmpy);
    }
    check_game_over(sock);
    return ;
}

void destroy_wall(int sock, int x, int y)
{
    EGB_Entity *wall, *floor;
    char    *encoded_floor;

    wall = EGBS_FindEntityByPosition(
            (x * 100) + 350,
            y * 100,
            EGB_Position_Top
        );
    if (wall == NULL || strcmp(wall->name, "wall") != 0)
        return ;

    floor = create_floor(x, y);
    encoded_floor = EGB_Serializer_EncodeEntity(floor);
    broadcast_to_players(sock, encoded_floor, NULL);
    destroy_entity(sock, wall);
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

        log_debug("for player at (%d, %d)", pos->x, pos->y);

        player_x = floor(((pos->x + pos->width / 2) - 350) / 100);
        player_y = floor((pos->y + pos->height / 2) / 100);

        log_debug("he is on case (%d, %d) and the bomb explosed on (%d, %d)", player_x, player_y, x, y);

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
    networkable = EGB_Component_CreateNetworkable();

    EGB_Component_AddToEntity(explosion, position);
    EGB_Component_AddToEntity(explosion, networkable);

    encoded_explosion = EGB_Serializer_EncodeEntity(explosion);
    broadcast_to_players(sock, encoded_explosion, NULL);
}
