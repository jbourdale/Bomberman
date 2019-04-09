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
    char                **file_names; // it's an array of file to be able to create animations
    SDL_Texture         **sprites; // Not sure exactly how we will work with that

    // ANIMATIONS
    int                 current_frame; // animation frame
    int                 animate;
    Uint32              last_animation_tick;
    Uint32              animation_delai_frame;
}                       entity_t;

/*
 * components.c
 **/
int add_component_to_entity(entity_t *entity, void *component);
int add_components_to_entity(entity_t *entity, void **components);

/*
 * core.c
 **/
int add_filename_to_entity(entity_t *entity, char *filename);
int add_filenames_to_entity(entity_t *entity, char **filenames, int size);
entity_t *set_entity_position(entity_t *entity, int x, int y);
entity_t *set_entity_dimensions(entity_t *entity, int w, int h);

/*
 * event.c
 **/
//todo

/*
 * init.c
 **/
entity_t *_init_entity();
// entity_t *create_animated_entity(SDL_Renderer *renderer, char *name, char **filenames);
entity_t *create_entity(SDL_Renderer *renderer, char *name, char *filename);
entity_t *create_animated_entity(SDL_Renderer *renderer, char *name, char **filenames, int nb_filenames);
int destroy_entity(entity_t *entity);

/*
 * render.c
 **/
void _base_entity_render(SDL_Renderer *renderer, entity_t *entity);
void render_entitys(SDL_Renderer *renderer);

/*
 * sprites.c
 **/
int _create_entity_sprite(SDL_Renderer *renderer, entity_t *entity, char *filename);
int _create_entity_sprites(SDL_Renderer *renderer, entity_t *entity);

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
