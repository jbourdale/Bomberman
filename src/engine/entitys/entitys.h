#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "../engine.h"

typedef struct          entity_s {
    char                *name;
    void                **components;

    // EVENTS
    void                (*on_init)();
    void                (*on_click)();
    void                (*on_destroy)();
    // void             (*on_hover)(); // may cause perf problems

    // GRAPHICAL
    void                (*render)();
    int                 current_frame; // animation frame
    char                **file_names; // it's an array of file to be able to create animations
    SDL_Texture         **sprites; // Not sure exactly how we will work with that
    int                 animate;
    int                 displayed;
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
int add_filenames_to_entity(entity_t *entity, char **filename);
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
entity_t *create_animated_entity(SDL_Renderer *renderer, char *name, char **filenames);
entity_t *create_entity(SDL_Renderer *renderer, char *name, char *filename);
int destroy_entity(entity_t *entity);

/*
 * render.c
 **/
void _base_entity_render();

/*
 * sprites.c
 **/
int _create_entity_sprite(SDL_Renderer *renderer, entity_t *entity, char *filename);
int _create_entity_sprites(SDL_Renderer *renderer, entity_t *entity);

/*
 * manager.c
 **/
entity_t **entitys_manager();
int add_entity_to_manager(entity_t *entity);

#endif
