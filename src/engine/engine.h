#ifndef __ENGINE_H__
#define __ENGINE_H__

// Forward declaration
typedef struct entity_s entity_t;
typedef struct component_s component_t;
typedef struct position_component_s position_component_t;

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// LOGS
#include "../log/log.h"

// COMPONENTS
#include "./components/position/position.h"
#include "./components/components.h"

// ENTITY
#include "./entitys/entitys.h"

// SDL
#include "./sdl/sdl.h"

// SYSTEMS
#include "./systems/systems.h"

int start_engine(SDL_Window **window, SDL_Renderer **renderer);
int run_engine(SDL_Renderer *renderer);
int stop_engine(SDL_Window *window, SDL_Renderer *renderer);

#endif
