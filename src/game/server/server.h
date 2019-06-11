/*
** server.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __SERVER_H__
#define __SERVER_H__

#include "../game.h"

#define REQUEST_MAX_LENGTH 1024

// init.c
int init_server_socket(int port);
int is_server_running();
void stop_server();
void start_server();

// parsing.c
int parse_event_requests(int sock, char *event_request, player_t *player);
int parse_request(int sock, char *payload, struct sockaddr_in clientaddr);

// server.c
void *run_server(void *arg);
pthread_t start_server_thread();

// player.c
player_t *find_player_by_addr(struct sockaddr_in clientaddr);

// entities.c
void handle_entity_destruction(int sock, char *raw);
void handle_entities_request(int sock, char *raw, player_t *player);

#endif
