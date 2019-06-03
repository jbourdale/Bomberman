/*
** server.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "server.h"
#include "state/state.h"

pthread_cond_t SERVER_INIT_DONE_COND = PTHREAD_COND_INITIALIZER;
pthread_mutex_t SERVER_INIT_DONE_MUTEX = PTHREAD_MUTEX_INITIALIZER;

void *run_server(void *arg) {
    struct sockaddr_in clientaddr;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    int server_sock;
    char *request;

    log_debug("arg : %p", arg);

    server_sock = init_server_socket(1337);
    if (server_sock < 0) {
        return NULL;
    }
    init_game();
    pthread_cond_signal(&SERVER_INIT_DONE_COND);
    while(1) {
        request = malloc(REQUEST_MAX_LENGTH);
        memset(request, '\0', REQUEST_MAX_LENGTH);
        recvfrom(server_sock, (char *)request, REQUEST_MAX_LENGTH, MSG_WAITALL,
            (struct sockaddr *) &clientaddr, &addrlen);

        parse_request(server_sock, request, clientaddr);

        // sendto(server_sock, (const char *)request, strlen(request), 0,
        //     (const struct sockaddr *) &clientaddr, addrlen);
    }
}

pthread_t start_server_thread()
{
    pthread_t server_th;

    if(pthread_create(&server_th, NULL, run_server, NULL) == -1) {
        return (pthread_t) -1;
    }
    pthread_cond_wait(&SERVER_INIT_DONE_COND, &SERVER_INIT_DONE_MUTEX);

    return server_th;
}
