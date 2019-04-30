#ifndef __ENGINE_H__
#define __ENGINE_H__


// Forward declaration
typedef struct entity_s entity_t;
typedef struct component_s component_t;
typedef struct position_component_s position_component_t;
typedef struct animation_component_s animation_component_t;
typedef struct entity_manager_s entity_manager_t; 

// Va args
#include <stdarg.h>

// limits
#include <limits.h>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// LOGS
#include "../log/log.h"

// COMPONENTS
#include "./components/animation/animation.h"
#include "./components/position/position.h"
#include "./components/texture/texture.h"
#include "./components/fpsrate/fpsrate.h"
#include "./components/components.h"

// ENTITY
#include "./entitys/entitys.h"

// SDL
#include "./sdl/sdl.h"

// SYSTEMS
#include "./systems/systems.h"
#include "./systems/position/position.h"

// EVENTS
#include "./events/events.h"


// TOOLS
#include "./tools/entitys/fps_indicator/fps_indicator.h"

int start_engine();
int run_engine();
int stop_engine();

void move_position_component_right(position_component_t *comp, int offset);
void move_position_component_left(position_component_t *comp, int offset);
void move_position_component_up(position_component_t *comp, int offset);
void move_position_component_down(position_component_t *comp, int offset);

void start_framerate_regulation();
void regulate_frame_rate();

int create_sprite(SDL_Renderer* renderer, char *filename, SDL_Texture **sprite);

#endif
