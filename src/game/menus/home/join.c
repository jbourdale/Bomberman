/*
** join.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "home.h"
#include "../../game.h"

void on_join_text_input(EGB_Entity *modal, SDL_Event e)
{
    char *input;
    char key;

    if (e.type == SDL_KEYUP)
        return;

    input = (char *)SDL_GetKeyName(e.key.keysym.sym);
    key = input[0];

    if (key < '0' || key > '9')
        return;

    log_debug("Text input on : %s > %s", modal->name, SDL_GetKeyName(e.key.keysym.sym));
}

void on_join_start_btn_click()
{

}

void create_join_start_btn() {
    EGB_Entity                 *btn;
    EGB_Component_Position     *pos_comp;
    EGB_Component_Texture      *texture_comp;
    EGB_Component_Event        *click_event;

    btn = EGB_Entity_Create("btn_join_start");
    click_event = EGB_Component_CreateEventClick(on_join_start_btn_click);
    pos_comp = EGB_Component_CreatePosition(887, 625, EGB_Position_AlwaysOnTop, 145, 152);
    texture_comp = EGB_Component_CreateTexture("menus/btn_join.png");

    EGB_Component_AddToEntity(btn, click_event);
    EGB_Component_AddToEntity(btn, pos_comp);
    EGB_Component_AddToEntity(btn, texture_comp);
}

void create_join_modal()
{
	EGB_Entity 				*modal;
	EGB_Component_Position 	*pos;
	EGB_Component_Texture 	*texture;
	EGB_Component_Event 	*keyboard;

	modal = EGB_Entity_Create("join_modal");
	pos = EGB_Component_CreatePosition(496, 169, EGB_Position_Top, 927, 742);
	texture = EGB_Component_CreateTexture("menus/join.png");
	keyboard = EGB_Component_CreateEventKeyStroke(on_join_text_input);

	EGB_Component_AddToEntity(modal, pos);
	EGB_Component_AddToEntity(modal, texture);
	EGB_Component_AddToEntity(modal, keyboard);

	create_join_start_btn();
}


