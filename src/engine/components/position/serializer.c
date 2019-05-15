/*
** serializer.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "./position.h"

char    *EGB_Component_PositionSerializer(void **comp)
{
    EGB_Component_Position  *position_component;
    char *payload;

    log_debug("EGB_Component_PositionSerializer");
    payload = malloc(1000);
    position_component = (EGB_Component_Position *)*comp;
    sprintf(payload, "position_component;%d;%d;%d;%d;%d",
        position_component->x,
        position_component->y,
        position_component->z,
        position_component->width,
        position_component->height
    );
    return payload;
}
