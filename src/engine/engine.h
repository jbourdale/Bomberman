#ifndef __ENGINE_H__
#define __ENGINE_H__

// Forward declaration
typedef struct entity_s entity_t;
typedef struct component_s component_t;
typedef struct position_component_s position_component_t;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../log/log.h"
#include "./components/position/position.h"
#include "./components/components.h"
#include "./entitys/entitys.h"
#include "./sdl/sdl.h"
#include "./systems/systems.h"

#endif
