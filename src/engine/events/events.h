#ifndef __EVENTS_H__
#define __EVENTS_H__

#include "../engine.h"

int handle_events();
int handle_entitys_click(SDL_Event e);
int             handle_entity_key_events(SDL_Event e);

#endif
