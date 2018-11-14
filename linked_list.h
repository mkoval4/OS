

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "stdlib.h"

struct linked_list
{
   	void *value;
   	struct linked_list *next;
};

struct linked_list* init_linked_list();

#endif