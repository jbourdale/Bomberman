/*
** networkable.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "networkable.h"

networkable_component_t    				*create_networkable_component()
{
	static networkable_entity_list_t 	**registered_entity_list = NULL;
    networkable_component_t    			*component;

    if (registered_entity_list == NULL)
    {
    	registered_entity_list = malloc(sizeof(networkable_entity_list_t *));
    	registered_entity_list[0] = NULL;
    }

    component = malloc(sizeof(networkable_component_t));
    component->name = strdup("networkable_component");
    return component;
}

int 		find_entity_id_by_name(networkable_entity_list_t **registered_entity_list, char *entity_name)
{
	int 	i;

	i = 0;
	while (registered_entity_list[i] != NULL)
	{
		if (strcmp(registered_entity_list[i]->entity_name, entity_name) == 0)
			return registered_entity_list[i]->entity_id;
		i++;
	}
	return -1;
}

networkable_entity_list_t 				**register_networkable_entity(char* entity_name)
{
	static networkable_entity_list_t 	**registered_entity_list = NULL;
	int 								i;
	networkable_entity_list_t			*new_entry;

	// init
	if (registered_entity_list == NULL)
    {
    	registered_entity_list = malloc(sizeof(networkable_entity_list_t *));
    	registered_entity_list[0] = NULL;
    }

    // retrieve
    if (entity_name == NULL)
    	return registered_entity_list;

    // add
	if (find_entity_id_by_name(registered_entity_list, entity_name) != -1)
		return -1;

	i = 0;
	while (registered_entity_list[i] != NULL)
		i++;

	new_entry = malloc(sizeof(registered_entity_list *));
	new_entry->entity_name = strdup(entity_name);
	new_entry->entity_id = i;

	registered_entity_list = realloc(registered_entity_list, (i + 2) * sizeof(networkable_entity_list_t *));
	registered_entity_list[i] = new_entry;
	registered_entity_list[i+1] = NULL;

	return NULL;
}

int                         destroy_position_component(entity_t *entity)
{
    networkable_component_t    *comp;

    comp = (networkable_component_t *)find_component_by_name(entity, "networkable_component");
    if (comp == NULL)
        return 1;

    free(comp->name);
    free(comp);
    return 0;
}
