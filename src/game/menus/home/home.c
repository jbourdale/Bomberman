/*
** home.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "../../../engine/engine.h"
#include "home.h"

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

    create_join_btn();
    create_host_btn();
}

void on_join_btn_click () {
    log_debug("on join btn click");
}

void create_join_btn() {
    EGB_Entity                 *btn;
    EGB_Component_Position     *pos_comp;
    EGB_Component_Texture      *texture_comp;
    EGB_Component_Event        *click_event;

    btn = EGB_Entity_Create("btn_join");
    click_event = EGB_Component_CreateEventClick(on_join_btn_click);
    pos_comp = EGB_Component_CreatePosition(500, 300, EGB_Position_Classic, 1000, 100);
    texture_comp = EGB_Component_CreateTexture("btn_join.png");

    EGB_Component_AddToEntity(btn, click_event);
    EGB_Component_AddToEntity(btn, pos_comp);
    EGB_Component_AddToEntity(btn, texture_comp);
}

void on_host_btn_click() {
    log_debug("on host btn click");
}

void create_host_btn() {
    EGB_Entity                 *btn;
    EGB_Component_Position     *pos_comp;
    EGB_Component_Texture      *texture_comp;
    EGB_Component_Event        *click_event;

    btn = EGB_Entity_Create("btn_host");
    click_event = EGB_Component_CreateEventClick(on_host_btn_click);
    pos_comp = EGB_Component_CreatePosition(500, 500, EGB_Position_Classic, 1000, 100);
    texture_comp = EGB_Component_CreateTexture("btn_host.png");

    EGB_Component_AddToEntity(btn, click_event);
    EGB_Component_AddToEntity(btn, pos_comp);
    EGB_Component_AddToEntity(btn, texture_comp);
}