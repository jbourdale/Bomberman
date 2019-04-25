#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "../engine.h"

#define DEFAULT_ANIMATION_DELAI_FRAME 100

typedef struct          entity_s {
    char                *name;
    void                **components;

    // EVENTS
    void                (*on_init)();
    void                (*on_click)();
    void                (*on_destroy)();
    void                (*on_key_stroke)();
    // void             (*on_hover)(); // may cause perf problems

    // GRAPHICAL
    void                (*render)(SDL_Renderer* renderer, entity_t *self);
    int                 displayed;
}                       entity_t;

/*
 * components.c
 **/
int add_component_to_entity(entity_t *entity, void *component);
int add_components_to_entity(entity_t *entity, void **components);

/*
 * event.c
 **/
//todo

/*
 * init.c
 **/
entity_t *_init_entity();
entity_t *create_entity(char *name);
int destroy_entity(entity_t *entity);

/*
 * render.c
 **/
void _base_entity_render(SDL_Renderer *renderer, entity_t *entity);
void render_entitys();
void render_entity_texture(SDL_Renderer*, entity_t*, position_component_t*);
void render_entity_animation(SDL_Renderer*, entity_t *, animation_component_t**, position_component_t*);

/*
 * manager.c
 **/
entity_t **entitys_manager();
entity_t *find_first_entity_by_name(char *name);

/*
 * animate.c
 **/
void enable_entity_animation(entity_t *entity);
void disable_entity_animation(entity_t *entity);
void toggle_entity_animation(entity_t *entity);

#endif
