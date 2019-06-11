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
    EGB_Component_Textual *textual;
    EGB_Component_Position *pos;
    char *input;

    if (e.type == SDL_KEYUP)
        return;

    log_debug("Text input on : %s > %s", modal->name, SDL_GetKeyName(e.key.keysym.sym));
    textual = EGB_FindComponentByName(modal, "textual_component");
    pos = EGB_FindComponentByName(modal, "position_component");

    input = (char *)SDL_GetKeyName(e.key.keysym.sym);
    if (strcmp(input, "Backspace") == 0) {
        textual->text[strlen(textual->text) - 1] = '\0';
        pos->width = strlen(textual->text) * 50;
        return;
    } else if (strcmp(input, "Space") == 0) {
        pos->width = strlen(textual->text) * 50;
        textual->text = strcat(textual->text, ".");
        return;
    }

    if (input[0] < '0' || input[0] > '9')
        return ;

    EGB_Component_Textual_SetText(textual, strcat(textual->text, input));
    pos->width = strlen(textual->text) * 50;
}

void on_join_start_btn_click(EGB_Entity *start_btn)
{
    int error = 0;

    char *recvdata = malloc(1000);
    memset(recvdata, '\0', 1000);

    EGB_Entity *text_input, *modal;
    EGB_Component_Textual *textual;

    text_input = EGB_Entity_FindFirstByName("join_text_input");
    modal = EGB_Entity_FindFirstByName("join_modal");
    textual = EGB_FindComponentByName(text_input, "textual_component");

    EGB_Network_Configuration config= { strdup(textual->text), 1337 };
    log_debug("SET CONFIGURATION ON JOIN START BTN CLICK");
    EGB_Network_SetConfiguration(config);
    EGB_Network_Enable();

    EGB_Network_SendEvent("PING");
    
    log_debug("BEFORE TIMEOUT");
    SDL_Delay(2000);
    log_debug("TIMEOUT POP");

    log_debug("READABLE");
    if (recvfrom(EGB_Network_GetSocket(), recvdata, 1000, MSG_DONTWAIT, NULL, NULL) == -1) {
        log_debug("UNABLE TO READ");
        error = 1;
    }
    log_debug("recvdata : %s", recvdata);
    if (strcmp(recvdata, "PONG") != 0) {
        log_debug("RECIEVED SOMETHING ELSE THAT PONG");
        error = 1;
    }

    EGB_Entity_Destroy(text_input);
    EGB_Entity_Destroy(modal);
    EGB_Entity_Destroy(start_btn);

    log_debug("ERROR : %d", error);

    if (error == 0)
        start_game();
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

	modal = EGB_Entity_Create("join_modal");
	pos = EGB_Component_CreatePosition(496, 169, EGB_Position_Top, 927, 742);
	texture = EGB_Component_CreateTexture("menus/join.png");

	EGB_Component_AddToEntity(modal, pos);
	EGB_Component_AddToEntity(modal, texture);

	create_join_start_btn();
    create_text_input();
}

void create_text_input() {
    EGB_Entity  *text_input;
    EGB_Component_Position *pos;
    EGB_Component_Textual *textual;
	EGB_Component_Event 	*keyboard;

    text_input = EGB_Entity_Create("join_text_input");
	keyboard = EGB_Component_CreateEventKeyStroke(on_join_text_input);
    pos = EGB_Component_CreatePosition(600, 500, EGB_Position_AlwaysOnTop, 0, 100);
    textual = EGB_Component_CreateTextual("", "spacefont.ttf");

    EGB_Component_AddToEntity(text_input, keyboard);
    EGB_Component_AddToEntity(text_input, pos);
    EGB_Component_AddToEntity(text_input, textual);
}


