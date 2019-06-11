/*
** textual.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "textual.h"

EGB_Component_Textual    *EGB_Component_CreateTextual(char *text, char *font)
{
    EGB_Component_Textual *comp;

    comp = malloc(sizeof(EGB_Component_Textual));
    comp->name = strdup("textual_component");
    comp->text = strdup(text);
    comp->font_resource = EGB_Get_Resource(font);

    return comp;
}

int     EGB_Component_Textual_SetText(EGB_Component_Textual *comp, char *new_text)
{
    char *new = strdup(new_text);

    if (comp == NULL)
        return 1;

    if (comp->text != NULL)
        free(comp->text);

    comp->text = new;
    return 0;
}

int         EGB_Component_DestroyTextual() {
    return 1;
}
