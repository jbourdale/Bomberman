/*
** network.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "network.h"
SOCKET EGB_Network_UDPsock = -1;

int                 EGB_Network_Handle()
{
    static fd_set   readfs;
    static struct   timeval tv;
    int             ret = 0;
    char            *recvdata;
    tv.tv_sec = 0;
    tv.tv_usec = 100;

    if (!EGB_Network_IsEnabled()) {
        return EGB_NETWORK_DISABLED;
    }

    if (EGB_Network_UDPsock == -1)
        EGB_Network_UDPsock = socket(AF_INET, SOCK_DGRAM, 0);

    FD_ZERO(&readfs);
    FD_SET(EGB_Network_UDPsock, &readfs);

    if ((ret = select(EGB_Network_UDPsock + 1, &readfs, NULL, NULL, &tv)) < 0)
    {
        log_error("NETWORK ERROR");
        return EGB_NETWORK_ERROR;
    }

    if (!FD_ISSET(EGB_Network_UDPsock, &readfs))
        return EGB_NETWORK_NODATA;

    recvdata = malloc(1000);
    memset(recvdata, '\0', 1000);
    if (recvfrom(EGB_Network_UDPsock, (char*)recvdata, 1000, 0, NULL, NULL) == -1)
        return EGB_NETWORK_ERROR;
    switch (recvdata[0]) {
        case EGB_EVENT_NETWORK_IDENTIFIER:
            EGB_Network_ParseEventRequest(recvdata);
            break;
        case EGB_ERROR_NETWORK_IDENTIFIER:
            break;
        case EGB_ENTITY_NETWORK_IDENTIFIER:
            EGB_Serializer_DecodeEntities(recvdata);
            break;
        default:
            log_debug("RECV UNPARSABLE DATA");
    }

    return EGB_NETWORK_SUCCESS;
}


int                         EGB_Network_SendEntity(EGB_Entity *entity)
{
    char                    *encodedEntity;
    int                     sendtoSuccess;
    struct sockaddr_in      servaddr;

    if (!EGB_Network_IsEnabled())
        return EGB_NETWORK_DISABLED;

    encodedEntity = EGB_Serializer_EncodeEntity(entity);
    if (encodedEntity == NULL)
        return 1;

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(EGB_Network_GetConfiguration().port);
    servaddr.sin_addr.s_addr = inet_addr(EGB_Network_GetConfiguration().ip);

    sendtoSuccess = sendto(
        EGB_Network_UDPsock,
        (const char *)encodedEntity,
        strlen(encodedEntity),
        0,
        (const struct sockaddr*) &servaddr,
        sizeof(servaddr)
    );
    return sendtoSuccess;
}

int       EGB_Network_DestroyEntity(EGB_Entity *entity)
{
    EGB_Component_Networkable *networkable_comp;
    char  *payload;
    struct sockaddr_in      servaddr;

    networkable_comp = EGB_FindComponentByName(entity, "networkable_component");
    if (networkable_comp == NULL)
        return -1;

    // log_debug("Sending destruction of Entity %s", networkable_comp->id);

    payload = malloc(1000);
    payload[0] = EGB_ENTITY_NETWORK_IDENTIFIER;
    payload[1] = EGB_NETWORK_VALUE_SEPARATOR_CHAR;
    payload[2] = '\0';
    strcat(payload, networkable_comp->id);
    strcat(payload, EGB_NETWORK_VALUE_SEPARATOR);
    strcat(payload, "0"); // network ownership 
    strcat(payload, EGB_NETWORK_VALUE_SEPARATOR);
    strcat(payload, "destroy#");

    // log_debug("payload : %s", payload);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(EGB_Network_GetConfiguration().port);
    servaddr.sin_addr.s_addr = inet_addr(EGB_Network_GetConfiguration().ip);

    return sendto(
        EGB_Network_UDPsock,
        (const char *)payload,
        strlen(payload),
        0,
        (const struct sockaddr*) &servaddr,
        sizeof(servaddr)
    );
}

int     EGB_Network_SendEvent(char *event) {
    char *payload;
    struct sockaddr_in      servaddr;

    payload = malloc(1000);
    payload[0] = EGB_EVENT_NETWORK_IDENTIFIER;
    payload[1] = EGB_NETWORK_VALUE_SEPARATOR_CHAR;
    payload[2] = '\0';
    strcat(payload, event);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(EGB_Network_GetConfiguration().port);
    servaddr.sin_addr.s_addr = inet_addr(EGB_Network_GetConfiguration().ip);

    return sendto(
        EGB_Network_UDPsock,
        (const char *)payload,
        strlen(payload),
        0,
        (const struct sockaddr*) &servaddr,
        sizeof(servaddr)
    );
}
