
#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include "linked_list.h"

typedef struct
{
	struct linked_list *head, *tail;
	int size;
} linked_stack_t;

linked_stack_t* init_linked_stack(void*);
void push(linked_stack_t*, void*);
void* pop(linked_stack_t*);
#endif