/*
** counter.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __COMPONENT_COUNTER_H__
#define __COMPONENT_COUNTER_H__

#include "../../engine.h"

typedef struct          EGB_Component_Counter_s
{
    char        *name;
    int         counter;
    int 		max;
}                       EGB_Component_Counter;

EGB_Component_Counter 	*EGB_Component_CreateCounter(int counter, int max);
char    			*EGB_Component_CounterSerializer(void **comp);
void                *EGB_Component_CounterUnserializer(char *raw);
int 				EGB_Component_DestroyCounter();

#endif