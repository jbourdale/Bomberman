#ifndef __EVENTS_H__
#define __EVENTS_H__

#include "../engine.h"

int EGB_Event_Handle();
int EGB_Event_HandleClick(SDL_Event e);
int EGB_Event_HandleKeyStroke(SDL_Event e);

#endif
