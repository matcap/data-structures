#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

typedef struct linked_list_s*  linked_list;    // Structure representing a single linked list of nodes

// Allocates memory for a new list
linked_list list_new(size_t elem_size);

// Appends the element to the list
void list_add_tail(linked_list list, const void* elem);

// Prepends the element to the list
void list_add_head(linked_list list, const void* elem);

// Gets element corresponding to index
void* list_get(linked_list list, const int index);

// Sets element corresponding to index
void list_set(linked_list list, const int index, const void* elem);

// Removes an element in the list
void list_remove(linked_list list, const int index);

// Returns list size
size_t list_size(linked_list list);

// Deallocats memory
void list_delete(linked_list list);

#endif // LINKED_LIST_H
