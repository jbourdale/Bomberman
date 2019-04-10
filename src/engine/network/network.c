/*
** network.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "network.h"

void *run_network(void *arg)
{
    (void) arg;
    log_debug("Run network thread");
    while (!game_over())
    {

    }
    pthread_exit(NULL);
}

int             launch_network_thread(pthread_t *thread)
{
    log_debug("launch_network_thread");
    if(pthread_create(thread, NULL, run_network, NULL) == - 1)
    {
        log_error("Error starting thread");
        return 1;
    }

    return 0;
}

int     wait_network_thread(pthread_t thread)
{
    if (pthread_join(thread, NULL))
    {
        log_error("error joining network thread");
        return 1;
    }
    return 0;
}


