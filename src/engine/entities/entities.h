#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "../engine.h"

typedef struct          EGB_Entity_s {
    char                *name;
    void                **components;

    // EVENTS
    void                (*on_destroy)();

    // GRAPHICAL
    void                (*render)(SDL_Renderer* renderer, EGB_Entity *self);
    int                 displayed;
}                       EGB_Entity;

typedef struct EGB_Entity_Manager_Element_s EGB_Entity_Manager_Element;
struct                          EGB_Entity_Manager_Element_s
{
    EGB_Entity                    *entity;
    EGB_Entity_Manager_Element     *next;
};

typedef struct                  EGB_Entity_Manager_s
{
    EGB_Entity_Manager_Element     *first;
}                               EGB_Entity_Manager;

/*
 * components.c
 **/
int EGB_Component_AddToEntity(EGB_Entity *entity, void *component);
int EGB_Component_AddManyToEntity(EGB_Entity *entity, void **components);
int EGB_Observables_RegisterEntity(EGB_Entity *entity, EGB_Component *component);

/*
 * init.c
 **/
EGB_Entity  *EGB_Entity_Copy(EGB_Entity *entity);
EGB_Entity  *EGB_Entity_Create(char *name);
int         EGB_Entity_Destroy(EGB_Entity *entity);

/*
 * render.c
 **/
void EGB_Entity_DefaultRenderer(SDL_Renderer *renderer, EGB_Entity *entity);
void EGB_Render_Entities();
void EGB_Render_EntityTexture(SDL_Renderer*, EGB_Entity*, EGB_Component_Position*);
void EGB_Render_EntityAnimation(SDL_Renderer*, EGB_Entity *, EGB_Component_Animation**, EGB_Component_Position*);

/*
 * observable.c
 **/
EGB_Entity_Manager    *EGB_Manager_Entity(Uint32 flags, ...);
EGB_Entity            *EGB_Entity_FindFirstByName(char *name);

#define EGB_Manager_Retrieve            0x0001
#define EGB_Manager_Add                 0x0010
#define EGB_Manager_Delete              0x0100
#define EGB_Resources_Manager_Set_Dir   0x1000

#endif
