/*
** entities.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "server.h"

void handle_entities_request(int sock, char *raw) 
{
	if (strstr(raw, "destroy") != NULL) {
		// if a bomb is destroyed
		log_debug("A ENTITY HAVE BEEN DESTROYED");
	}

    broadcast_to_players(sock, raw);
}

int strpos(char *haystack, char *needle)
{
   char *p = strstr(haystack, needle);
   if (p)
      return p - haystack;
   return -1;   // Not found = -1.
}