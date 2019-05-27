/*
** map.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "../../../engine/engine.h"
#include "state.h"

void create_wall_entity(int x, int y)
{
    EGB_Entity *wall;
    EGB_Component_Texture *texture_comp;
    EGB_Component_Position *pos_comp;
    EGB_Component_Collision *collision_comp;
    EGB_Component_Networkable *networkable_comp;

    wall = EGBS_Entity_Create("wall");
    texture_comp = EGB_Component_CreateTexture("wall.png");
    pos_comp = EGB_Component_CreatePosition((x * 100) + 350, y * 100, EGB_Position_Top, 100, 100);
    collision_comp = EGB_Component_CreateCollision(1);
    networkable_comp = EGB_Component_CreateNetworkable();
    EGB_Component_AddToEntity(wall, texture_comp);
    EGB_Component_AddToEntity(wall, pos_comp);
    EGB_Component_AddToEntity(wall, collision_comp);
    EGB_Component_AddToEntity(wall, networkable_comp);
}

void create_indestructible_wall(int x, int y)
{
    EGB_Entity *wall;
    EGB_Component_Texture *texture_comp;
    EGB_Component_Position *pos_comp;
    EGB_Component_Collision *collision_comp;
    EGB_Component_Networkable *networkable_comp;

    wall = EGBS_Entity_Create("indestructible_wall");
    texture_comp = EGB_Component_CreateTexture("indestructible_wall.png");
    pos_comp = EGB_Component_CreatePosition((x * 100) + 350, y * 100, EGB_Position_Top, 100, 100);
    collision_comp = EGB_Component_CreateCollision(1);
    networkable_comp = EGB_Component_CreateNetworkable();
    EGB_Component_AddToEntity(wall, texture_comp);
    EGB_Component_AddToEntity(wall, pos_comp);
    EGB_Component_AddToEntity(wall, collision_comp);
    EGB_Component_AddToEntity(wall, networkable_comp);
}

void create_outer_wall(int x, int y)
{
    EGB_Entity *wall;
    EGB_Component_Texture *texture_comp;
    EGB_Component_Position *pos_comp;
    EGB_Component_Collision *collision_comp;
    EGB_Component_Networkable *networkable_comp;

    wall = EGBS_Entity_Create("outer_wall");
    texture_comp = EGB_Component_CreateTexture("outer_wall.png");
    pos_comp = EGB_Component_CreatePosition((x * 100) + 350, y * 100, EGB_Position_Top, 100, 100);
    collision_comp = EGB_Component_CreateCollision(1);
    networkable_comp = EGB_Component_CreateNetworkable();
    EGB_Component_AddToEntity(wall, texture_comp);
    EGB_Component_AddToEntity(wall, pos_comp);
    EGB_Component_AddToEntity(wall, collision_comp);
    EGB_Component_AddToEntity(wall, networkable_comp);
}

void create_floor(int x, int y)
{
    EGB_Entity *floor;
    EGB_Component_Texture *texture_comp;
    EGB_Component_Position *pos_comp;
    EGB_Component_Networkable *networkable_comp;

    floor = EGBS_Entity_Create("floor");
    texture_comp = EGB_Component_CreateTexture("floor.png");
    pos_comp = EGB_Component_CreatePosition((x * 100) + 350, y * 100, EGB_Position_Background, 100, 100);
    networkable_comp = EGB_Component_CreateNetworkable();

    EGB_Component_AddToEntity(floor, texture_comp);
    EGB_Component_AddToEntity(floor, pos_comp);
    EGB_Component_AddToEntity(floor, networkable_comp);
}