#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "../engine.h"
#include <pthread.h>

void *run_network(void *arg);
int launch_network_thread(pthread_t *thread);
int wait_network_thread(pthread_t thread);

#endif
