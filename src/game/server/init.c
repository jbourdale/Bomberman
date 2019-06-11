/*
** init.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "server.h"

int is_running = 1;
int init_server_socket(int port) {
    int sockfd;
    struct sockaddr_in servaddr;
    log_debug("Starting server on port %d", port);

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        log_debug("UNABLE TO CREATE SOCKET");
        return -1;
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        log_debug("UNABLE TO BIND");
        return -1;
    }
    log_debug("Listening '0.0.0.0' on %d...", port);
    return sockfd;
}

void stop_server()
{
    EGB_Entity_Manager          *manager;
    EGB_Entity_Manager_Element  *iterator;

    // clear all entities
    manager = EGBS_Manager_Entity(EGB_Manager_Retrieve);
    if (manager != NULL) {
        iterator = manager->first;
        while (iterator != NULL) {
            EGBS_Entity_Destroy(iterator->entity);
            iterator = iterator->next;
        }
    }
    is_running = 0;
}

void start_server()
{
    is_running = 1;
}

int is_server_running() 
{
    return is_running;
}