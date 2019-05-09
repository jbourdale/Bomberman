/*
** collision.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "collision.h"
/**
 * @brief      Collision entity manager. Store entity that have collision enable
 *
 * @param      flags      The flags
 * @param      entity[optional]  The entity to add. Require flag EGB_Manager_Add
 *
 * @note Availible flag :
 *  <ul>
 *      <li>EGB_Manager_Retrieve</li>
 *      <li>EGB_Manager_Add</li>
 *      <li>EGB_Manager_Delete</li>
 *  </ul>
 *
 * @return     if flag EGB_Manager_Retrieve is sent, return the manager. Overwise, return NULL
 */
EGB_Entity_Manager              *EGB_Manager_Collision(Uint32 flags, ...)
{
    static EGB_Entity_Manager   *manager;
    EGB_Entity_Manager_Element  *entity_iterator, *entry;
    EGB_Entity                  *entity;
    va_list                     argp;


    if (flags & EGB_Manager_Retrieve)
        return manager;
    if (flags & EGB_Manager_Add)
    {
        va_start(argp, flags);
        entity = va_arg(argp, EGB_Entity*);
        va_end(argp);
        if (entity == NULL)
            return NULL;

        entry = malloc(sizeof(EGB_Entity_Manager_Element));
        entry->entity = entity;
        entry->next = NULL;

        if (manager == NULL) {
            manager = malloc(sizeof(EGB_Entity_Manager));
            manager->first = entry;
            return NULL;
        }
        entity_iterator = manager->first;
        while (entity_iterator->next != NULL)
            entity_iterator = entity_iterator->next;
        entity_iterator->next = entry;
        return NULL;
    }
    if (flags & EGB_Manager_Delete) {
        return NULL;
    }
    return NULL;
}

/**
 * @brief      Create a Collision component
 *
 * @note       If the collision component of an entity is active, he will collide
 * with all component that are above him in their EGB_Component_Position and
 * also have a active collide component. You need to use the specific function
 * (as follow) to apply collision
 * <ul>
 * 	<li>EGB_Position_Move_Left()</li>
 * 	<li>EGB_Position_Move_Right()</li>
 * 	<li>EGB_Position_Move_Up()</li>
 * 	<li>EGB_Position_Move_Down</li>
 * </ul>
 *
 * @param      f     callback
 *
 * @return     Event click component created
 */
EGB_Component_Collision *EGB_Component_CreateCollision(int active)
{
    EGB_Component_Collision   *component;

    component = malloc(sizeof(EGB_Component_Collision));
    component->name = strdup("collision_component");
    component->active = active;
    return component;
}

/**
 * @brief      Destroy the Collision component from entity
 *
 * @param      entity  The entity
 *
 * @return     status
 *              <ul>
 *                  <li>0 = Component successfuly destroy</li>
 *                  <li>1 = An error occured</li>
 *              </ul>
 */
int EGB_Component_DestroyCollision(EGB_Entity *entity)
{
    EGB_Component_Collision       *comp;

    comp = (EGB_Component_Collision *)EGB_FindComponentByName(entity, "collision_component");
    if (comp == NULL)
        return 1;

    free(comp->name);
    free(comp);
    return 0;
}

/**
 * @brief      Detect if position component is colliding another entity
 *
 * @param      position  The position component to test
 *
 * @TODO       evolve with collide box
 *
 * @return     Return the position component that the entity collide, otherwise NULL
 */
int                                 EGB_Collide(
    EGB_Entity                      *entity,
    EGB_Component_Position          *collision
) {
	EGB_Entity_Manager 				*manager;
	EGB_Entity_Manager_Element      *manager_iterator;
	EGB_Entity 						*manager_entity;
	EGB_Component_Collision 		*entity_collision;
	EGB_Component_Position 			*entity_position_comp, *tmp_entity_pos_comp;
	SDL_Rect 						entity_collision_box, tmp_entity_collision;

	entity_position_comp = (EGB_Component_Position *)EGB_FindComponentByName(
		entity,
		"position_component"
	);
	if (entity_position_comp == NULL)
		return 0;
	EGB_Component_PositionToRect(entity_position_comp, &entity_collision_box);

	manager = EGB_Manager_Collision(EGB_Manager_Retrieve);
	manager_iterator = manager->first;
	while (manager_iterator != NULL) {
		manager_entity = manager_iterator->entity;
        if (manager_entity != entity) {
    		entity_collision = (EGB_Component_Collision *)EGB_FindComponentByName(
    			manager_entity,
    			"collision_component"
    		);
    		if (entity_collision->active == 1) {
    			tmp_entity_pos_comp = (EGB_Component_Position *)EGB_FindComponentByName(
    				manager_entity,
    				"position_component"
    			);
    			if (entity_collision != NULL &&
                    tmp_entity_pos_comp->z >= entity_position_comp->z
                ) {
    				EGB_Component_PositionToRect(
                        tmp_entity_pos_comp,
                        &tmp_entity_collision
                    );
    				if (SDL_HasIntersection(&entity_collision_box, &tmp_entity_collision))
                    {
    					// TODO use collide box
                        collision->x = tmp_entity_collision.x;
                        collision->y = tmp_entity_collision.y;
                        collision->width = tmp_entity_collision.w;
                        collision->height = tmp_entity_collision.h;
                        return 1;
    				}
    			}
    		}
        }
		manager_iterator = manager_iterator->next;
	}
	return 0;
}
