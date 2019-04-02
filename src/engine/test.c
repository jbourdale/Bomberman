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
    printf("### Starting engine test\n");

    printf("Creating an entity\n");
    entity_t *entity = create_entity("bonhomme", NULL);
    printf("entity name created : %s (must be 'bonhomme')\n", entity->name);

    printf("Creating a position component\n");
    position_component_t *pos_comp = create_position_component(0, 1, 2, 3);
    printf("Position component created : (%d,%d,%d,%d) must be (0,1,2,3)\n",
        pos_comp->x,
        pos_comp->y,
        pos_comp->width,
        pos_comp->height
    );

    printf("Attaching the component to the entity bonhomme \n");
    add_component_to_entity(entity, (void *)pos_comp);
    printf("first component of entity bonhomme : (%d,%d,%d,%d) must be (0,1,2,3)",
        ((position_component_t *)entity->components[0])->x,
        ((position_component_t *)entity->components[0])->y,
        ((position_component_t *)entity->components[0])->width,
        ((position_component_t *)entity->components[0])->height
    );
    return 1;
}
