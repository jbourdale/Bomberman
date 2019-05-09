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

    recvdata = malloc(1024);
    recvfrom(EGB_Network_UDPsock, (char*)recvdata, 1024, 0, NULL, NULL);
    log_debug("recvdata : %s", recvdata);
    switch (recvdata[0]) {
        case EGB_EVENT_NETWORK_IDENTIFIER:
            break;
        case EGB_ERROR_NETWORK_IDENTIFIER:
            break;
        case EGB_ENTITY_NETWORK_IDENTIFIER:
            EGB_Serializer_DecodeEntity(recvdata);
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


    log_debug("sending entity %s", entity->name);
    encodedEntity = EGB_Serializer_EncodeEntity(entity);
    if (encodedEntity == NULL)
        return 1;
    log_debug("encodedEntity : %s", encodedEntity);

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
