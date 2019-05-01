#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "../engine.h"

#define DEFAULT_ANIMATION_DELAI_FRAME 100

typedef struct          entity_s {
    char                *name;
    void                **components;

    // EVENTS
    void                (*on_destroy)();

    // GRAPHICAL
    void                (*render)(SDL_Renderer* renderer, entity_t *self);
    int                 displayed;
}                       entity_t;

typedef struct entity_linked_list_el_s entity_linked_list_el_t;
struct                          entity_linked_list_el_s
{
    entity_t                    *entity;
    entity_linked_list_el_t     *next;
};

typedef struct                  entity_manager_s 
{
    entity_linked_list_el_t     *first;
}                               entity_manager_t;

/*
 * components.c
 **/
int add_component_to_entity(entity_t *entity, void *component);
int add_components_to_entity(entity_t *entity, void **components);
int register_entity_to_managers(entity_t *entity, component_t *component);

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
entity_manager_t *entitys_manager(Uint32 flags, ...);
void add_entity_to_manager(entity_manager_t *manager, entity_t *entity);
entity_t *find_first_entity_by_name(char *name);
#define EGB_Manager_Retrieve 1
#define EGB_Manager_Add 2
#define EGB_Manager_Delete 3

/*
 * animate.c
 **/
void enable_entity_animation(entity_t *entity);
void disable_entity_animation(entity_t *entity);
void toggle_entity_animation(entity_t *entity);

#endif
