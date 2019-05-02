#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "../engine.h"

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
int EGB_Component_AddToEntity(entity_t *entity, void *component);
int EGB_Component_AddManyToEntity(entity_t *entity, void **components);
int EGB_Observables_RegisterEntity(entity_t *entity, component_t *component);

/*
 * init.c
 **/
entity_t    *EGB_Entity_Create(char *name);
int         EGB_Entity_Destroy(entity_t *entity);

/*
 * render.c
 **/
void EGB_Entity_DefaultRenderer(SDL_Renderer *renderer, entity_t *entity);
void EGB_Render_Entities();
void EGB_Render_EntityTexture(SDL_Renderer*, entity_t*, position_component_t*);
void EGB_Render_EntityAnimation(SDL_Renderer*, entity_t *, animation_component_t**, position_component_t*);

/*
 * observable.c
 **/
entity_manager_t    *EGB_Observable_Entity(Uint32 flags, ...);
entity_t            *EGB_Entity_FindFirstByName(char *name);

#define EGB_Manager_Retrieve            0x0001
#define EGB_Manager_Add                 0x0010
#define EGB_Manager_Delete              0x0100
#define EGB_Resources_Manager_Set_Dir   0x1000

#endif
