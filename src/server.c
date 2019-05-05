/*
** server.c for  in /Bomberman/aljana_s
**
** Made by AL JANABI Sarah
** Login   <aljana_s@etna-alternance.net>
**
*/

// To compile, use command :
// gcc server.c -lpthread

#include "server.h"

void* my_server_socket(int argc, char **argv) {
	// Variables globales incluant l'initialisation du socket, du buffer, de la structure du socket de l'adresse Internet
	int socksudp;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;
	int len, n;


	// Création et initialisation du socket et de l'adresse du server
	socksudp = socket(AF_INET, SOCK_DGRAM, 0);

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT);

	// Initialisation du socket avec une gestion d'erreurs
	if ((socksudp) < 0) {
		perror("\nSocksudp : Could not create socket. :(");
		exit(EXIT_FAILURE);
	}


	// Lie le socket à une adresse avec une gestion d'erreurs
	if (bind(socksudp, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		perror("\nSocksudp : Bind error server. :(\n");
		exit(EXIT_FAILURE);
	}

	// Réception des données client 
	n = recvfrom(socksudp, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);

	memset(&servaddr, 0, sizeof(servaddr)); 
	// memset(&cliaddr, 0, sizeof(cliaddr)); 

	printf("Socket connection successful\n");

    buffer[n] = '\0';

} 

int main(void) {
	void* my_server_socket();
	printf("-------------------------------------------");
	printf("SERVER STARTED on port 5800");
	printf("-------------------------------------------");
    return 0;
}

// Future gestionnaire de lecture des données reçues par les sockets clients avec une utilisation de threads
void* connection_handler() {
	

	// Variables relatives au multithreading
	int i = 0;
	int error;
	int thread_lock = 0;
	pthread_mutex_t lock;
	pthread_mutex_t thread_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t thread_cond = PTHREAD_COND_INITIALIZER;


	/* Structure stockant les informations des threads clients et du magasin. */
typedef struct {
   int cliaddr;
   pthread_t thread_store;
   NB_CLIENTS = 4;
   pthread_t thread_clients [NB_CLIENTS];

}

	if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n Mutex init has failed\n"); 
        // return 1; 
	}

    while(i < 2) 
    { 
	error = pthread_create(&(threads_clients), NULL, thread_lock, NULL);
		if (error != 0) {
			printf("\nThread can't be created :[%s]", strerror(error)); 
		}
	}


	pthread_mutex_trylock(&thread_mutex);
	while(!thread_lock)
		pthread_cond_wait(&thread_lock, &thread_mutex);
	thread_lock = 0;
	pthread_mutex_unlock(&thread_mutex);

	pthread_join(tid[<thread_name>], NULL); 
	pthread_mutex_destroy(&lock); 

}