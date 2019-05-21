/*
** server.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "server.h"

void *run_server(void *arg) {
    struct sockaddr_in clientaddr;
    socklen_t len;
    int server_sock, n;
    char *request;

    log_debug("arg : %p", arg);

    server_sock = init_server_socket(1337);
    if (server_sock < 0) {
        return NULL;
    }
    init_game();
    while(1) {
        request = malloc(REQUEST_MAX_LENGTH);
        memset(request, '\0', REQUEST_MAX_LENGTH);
        n = recvfrom(server_sock, (char *)request, REQUEST_MAX_LENGTH, MSG_WAITALL,
            (struct sockaddr *) &clientaddr, &len);
        request[n] = '\n';
        log_debug("Recieved request : %s", request);

        sendto(server_sock, (const char *)request, strlen(request), 0,
            (const struct sockaddr *) &clientaddr, len);
    }
}

pthread_t start_server_thread()
{
    pthread_t server_th;

    if(pthread_create(&server_th, NULL, run_server, NULL) == -1) {
        return (pthread_t) -1;
    }

    return server_th;
}
