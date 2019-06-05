/*
** home.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "../../../engine/engine.h"
#include "home.h"
#include "../../player/player.h"
#include "../../server/server.h"

void    setup_home_menu() {
    EGB_Entity_Manager          *manager;
    EGB_Entity_Manager_Element  *iterator;

    // destroy all entities
    manager = EGB_Manager_Entity(EGB_Manager_Retrieve);
    if (manager != NULL) {
        iterator = manager->first;
        while (iterator != NULL) {
            EGB_Entity_Destroy(iterator->entity);
            iterator = iterator->next;
        }
    }

    create_background();
    create_join_btn();
    create_host_btn();
}

void on_game_end()
{
    log_debug("END GAME");
    setup_home_menu();
}

void on_game_start() {
    EGB_Network_RegisterEvent("END", on_game_end);
    create_start_countdown();
}

void start_game() {
    EGB_Entity_Destroy(EGB_Entity_FindFirstByName("btn_join"));
    EGB_Entity_Destroy(EGB_Entity_FindFirstByName("btn_host"));
    EGB_Entity_Destroy(EGB_Entity_FindFirstByName("background"));

    EGB_Network_RegisterEvent("START", on_game_start);
    EGB_Network_SendEvent("JOIN");
}

void create_background() {
    EGB_Entity  *background;
    EGB_Component_Position *pos;
    EGB_Component_Texture  *texture;

    EGB_Set_BackgroundColor(255, 155, 201, 255);

    background = EGB_Entity_Create("background");
    pos = EGB_Component_CreatePosition(0, 0, EGB_Position_Background, 1920, 1080);
    texture = EGB_Component_CreateTexture("menus/home.png");

    EGB_Component_AddToEntity(background, pos);
    EGB_Component_AddToEntity(background, texture);
}

void on_join_btn_click () {
    log_debug("on join btn click");
    start_game();
}

void create_join_btn() {
    EGB_Entity                 *btn;
    EGB_Component_Position     *pos_comp;
    EGB_Component_Texture      *texture_comp;
    EGB_Component_Event        *click_event;

    btn = EGB_Entity_Create("btn_join");
    click_event = EGB_Component_CreateEventClick(on_join_btn_click);
    pos_comp = EGB_Component_CreatePosition(1072, 811, EGB_Position_Classic, 182, 190);
    texture_comp = EGB_Component_CreateTexture("menus/btn_join.png");

    EGB_Component_AddToEntity(btn, click_event);
    EGB_Component_AddToEntity(btn, pos_comp);
    EGB_Component_AddToEntity(btn, texture_comp);
}

void on_start_game_btn_click(EGB_Entity *btn) {
    EGB_Entity_Destroy(btn);
    EGB_Network_SendEvent("START");
}

void on_host_btn_click() {
    EGB_Entity *start_game_btn;
    EGB_Component_Position *pos;
    EGB_Component_Texture *texture;
    EGB_Component_Event   *click;


    log_debug("on host btn click");
    start_server_thread();

    start_game();
    
    start_game_btn = EGB_Entity_Create("start_game_btn");
    pos = EGB_Component_CreatePosition(816, 390, EGB_Position_AlwaysOnTop, 287, 300);
    texture = EGB_Component_CreateTexture("menus/start_game.png");
    click = EGB_Component_CreateEventClick(on_start_game_btn_click);

    EGB_Component_AddToEntity(start_game_btn, pos);
    EGB_Component_AddToEntity(start_game_btn, click);
    EGB_Component_AddToEntity(start_game_btn, texture);

}

void create_host_btn() {
    EGB_Entity                 *btn;
    EGB_Component_Position     *pos_comp;
    EGB_Component_Texture      *texture_comp;
    EGB_Component_Event        *click_event;

    btn = EGB_Entity_Create("btn_host");
    click_event = EGB_Component_CreateEventClick(on_host_btn_click);
    pos_comp = EGB_Component_CreatePosition(670, 811, EGB_Position_Classic, 182, 190);
    texture_comp = EGB_Component_CreateTexture("menus/btn_host.png");

    EGB_Component_AddToEntity(btn, click_event);
    EGB_Component_AddToEntity(btn, pos_comp);
    EGB_Component_AddToEntity(btn, texture_comp);
}
