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

// server.c
void *run_server(void *arg);
pthread_t start_server_thread();

#endif
