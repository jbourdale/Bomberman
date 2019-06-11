/*
** init.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "server.h"

int init_server_socket(int port) {
    int sockfd;
    struct sockaddr_in servaddr;
    log_debug("Starting server on port %d", port);

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return -1;
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        return -1;
    }
    log_debug("Listening '0.0.0.0' on %d...", port);
    return sockfd;
}
