/*
** engine.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#ifndef __ENGINE_H__
#define __ENGINE_H__

// Forward declaration
typedef struct entity_s entity_t;
typedef struct component_s component_t;
typedef struct position_component_s position_component_t;
typedef struct animation_component_s animation_component_t;
typedef struct event_component_s event_component_t;
typedef struct entity_manager_s entity_manager_t;
typedef struct resource_s resource_t;
typedef struct resources_list_s resources_list_t;

// Va args
#include <stdarg.h>

// limits
#include <limits.h>

// directory handling
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// LOGS
#include "./log/log.h"

// FRAMERATE
#include "./framerate/framerate.h"

// COMPONENTS
#include "./components/animation/animation.h"
#include "./components/position/position.h"
#include "./components/texture/texture.h"
#include "./components/fpsrate/fpsrate.h"
#include "./components/components.h"
#include "./components/events/events.h"
#include "./components/events/click/click.h"
#include "./components/events/hover/hover.h"
#include "./components/events/keystroke/keystroke.h"

// RESOURCES
#include "./resources/resources.h"
#include "./resources/load/load.h"

// ENTITY
#include "./entities/entities.h"

// SDL
#include "./sdl/sdl.h"

// EVENTS
#include "./events/events.h"


// TOOLS
#include "./tools/entities/fps_indicator/fps_indicator.h"

int EGB_Run();
int EGB_Init();
int EGB_Quit();

int EGB_SDL_LoadTexture(SDL_Renderer* renderer, char *filename, SDL_Texture **sprite);

#endif
