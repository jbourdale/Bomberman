/*
** test.c for  in /home/dev/C/My_FTL/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include <stdio.h>
#include "engine.h"

int main()
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    log_info("### Starting engine test");

    log_info("starting engine");
    window = NULL;
    renderer = NULL;
    start_engine(window, renderer, ENGINE_NO_RUN);

    log_info("Creating an entity");
    entity_t *entity = create_entity(renderer, "bonhomme", NULL);
    log_info("entity name created : %s (must be 'bonhomme')", entity->name);

    log_info("Creating a position component");
    position_component_t *pos_comp = create_position_component(0, 1, 2, 3);
    log_info("Position component created : (%d,%d,%d,%d) must be (0,1,2,3)",
        pos_comp->x,
        pos_comp->y,
        pos_comp->width,
        pos_comp->height
    );

    log_info("Attaching the component to the entity bonhomme");
    add_component_to_entity(entity, (void *)pos_comp);
    log_info("first component of entity bonhomme : (%d,%d,%d,%d) must be (0,1,2,3)",
        ((position_component_t *)entity->components[0])->x,
        ((position_component_t *)entity->components[0])->y,
        ((position_component_t *)entity->components[0])->width,
        ((position_component_t *)entity->components[0])->height
    );

    log_info("Find component by name");
    pos_comp = (position_component_t*)find_component_by_name(entity, "position_component");
    log_info("Position component founded on entity : (%d,%d,%d,%d) must be (0,1,2,3)",
        pos_comp->x,
        pos_comp->y,
        pos_comp->width,
        pos_comp->height
    );
    log_info("Must return NULL when component not present"),
    pos_comp = (position_component_t*)find_component_by_name(entity, "fake_component");
    log_info("Position component founded on entity is NULL : (%d) must be (1)", pos_comp == NULL);


    log_info("delete position component");
    if (destroy_position_component(entity))
        log_error("delete failed");
    else
    {
        pos_comp = (position_component_t*)find_component_by_name(entity, "position_component");
        log_info("delete successful ? (must be 1 : %d)", pos_comp == NULL);
    }

    log_info("destroy entity");
    if (destroy_entity(entity))
        log_error("destroy entity failed");

    log_info("Creating entity with an image");
    entity = create_entity(renderer, "bonhomme", "./resources/mario.png");
    log_info("sprites successfuly created : %d (must be 1)", entity->sprites[0] != NULL);

    // DOESN'T WORK FOR NOW
    // log_info("Creating entity with an animation");
    // char **names = malloc(3 * sizeof(char *));
    // names[0] = strdup("./resources/mario.png");
    // names[1] = strdup("./resources/mario.png");
    // names[2] = strdup("./resources/mario.png");
    // entity = create_animated_entity("bonhomme", names);
    // log_info("sprites successfuly created : %d (must be 1)", entity->sprites[0] != NULL && entity->sprites[1] != NULL && entity->sprites[2] != NULL);

    return 1;
}
