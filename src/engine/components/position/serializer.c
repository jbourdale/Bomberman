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
    EGB_Component_Position  *position_component, *cpy;
    char *payload;

    if (comp == NULL)
        return "";

    log_debug("EGB_Component_PositionSerializer");
    position_component = (EGB_Component_Position *)*comp;

    cpy = malloc(sizeof(EGB_Component_Position));
    cpy->x = position_component->x;
    cpy->y = position_component->y;
    cpy->z = position_component->z;
    cpy->width = position_component->width;
    cpy->height = position_component->height;

    payload = malloc(1000);
    sprintf(payload, "position_component;%d;%d;%d;%d;%d",
        cpy->x,
        cpy->y,
        cpy->z,
        cpy->width,
        cpy->height
    );
    return payload;
}

void    *EGB_Component_PositionUnserializer(char *raw)
{
    EGB_Component_Position  *position_component;
    int     x, y, z, w, h;
    char    *token;
    log_debug("EGB_Component_PositionUnserializer");

    if (raw == NULL)
        return NULL;

    position_component = malloc(sizeof(EGB_Component_Position));

    log_debug("raw : %s", raw);

    token = strtok(raw, ";");
    token = strtok(NULL, ";");
    log_debug("token : %s", token);
    x = atoi(token);
    token = strtok(NULL, ";");
    log_debug("token : %s", token);
    y = atoi(token);
    token = strtok(NULL, ";");
    log_debug("token : %s", token);
    z = atoi(token);
    token = strtok(NULL, ";");
    log_debug("token : %s", token);
    w = atoi(token);
    token = strtok(NULL, ";");
    log_debug("token : %s", token);
    h = atoi(token);
    log_debug("UNSERIALIZE POSITION (%d, %d, %d, %d, %d)", x, y, z, w, h);

    return EGB_Component_CreatePosition(x, y, z, w, h);
}