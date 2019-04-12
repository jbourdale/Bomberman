/*
** core.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entitys.h"

int         add_filename_to_entity(entity_t *entity, char *filename)
{
    char    **tmp_filename;
    int     nb_filename;

    if (filename == NULL)
        return 1;
    log_debug("add_filename_to_entity, filename : %s", filename);

    tmp_filename = entity->file_names;
    nb_filename = 0;
    while (tmp_filename != NULL && *tmp_filename++)
        nb_filename++;

    log_debug("nb_filename : %d", nb_filename);
   
    log_debug("new_size : %d", (nb_filename + 2) * sizeof(char *));
    entity->file_names = realloc(entity->file_names, (nb_filename + 2) * sizeof(char *));
    entity->file_names[nb_filename] = strdup(filename);
    entity->file_names[nb_filename + 1] = NULL;

    log_debug("add_filename_to_entity end");
    return 0;
}

int         add_filenames_to_entity(entity_t *entity, char **filenames, int size)
{
    int     i;

    i = 0;
    while(i < size)
    {
        if (add_filename_to_entity(entity, filenames[i]))
        {
            destroy_entity(entity);
            return 1;
        }
        i++;
    }
    return 0;
}

