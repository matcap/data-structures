#include "linked_list.h"
#include <memory.h>

struct list_node{
    void* elem;                 // Stored element pointer
    struct list_node* next;     // Pointer to next node
};

struct linked_list_s{
    size_t elem_size;           // Size of the element in a node
    struct list_node* head;     // Pointer to head of list
    struct list_node* tail;     // Pointer to tail of list
    size_t size;                // List size
};


struct list_node* get_node_at(linked_list list, const int index){
    int count;              // Index counter
    struct list_node* n;    // Node iterator

    // Iterate the list from head, counting up to index
    for(n = list->head, count = 0;
        n != list->tail && count < index;
        n = n->next, count++){ }

    return n;
}


linked_list list_new(size_t elem_size){
    // Allocate memory for the linked list
    linked_list list = malloc(sizeof(struct linked_list_s));

    // Set fields
    list->elem_size = elem_size;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}


void list_delete(linked_list list){
    if(list == NULL)
        return;

    // Itearate through each node and free its memory
    struct list_node* next = list->head;
    while(next != NULL){
        struct list_node* temp = next->next;
        free(next->elem);
        free(next);
        next = temp;
    }

    // Free list struct memory
    free(list);
}


void list_add_head(linked_list list, const void *elem){
    // Allocate memory for a new node
    struct list_node* node = (struct list_node*) malloc(sizeof(struct list_node));

    // Allocate memory for the element inside the node
    node->elem = (void*) malloc(list->elem_size);

    // Copy element memory content int node element
    memcpy(node->elem, elem, list->elem_size);

    // Set node->next to current head
    node->next = list->head;

    // Handle the case in which tail is null
    if(list->tail == NULL){
        // Make tail point to new node
        list->tail = node;
    }

    // Set new node as head
    list->head = node;

    // Increase size
    list->size++;
}

void list_add_tail(linked_list list, const void *elem){
    // Allocate memory for a new node
    struct list_node* node = (struct list_node*) malloc(sizeof(struct list_node));

    // Allocate memory for the element inside the node
    node->elem = (void*) malloc(list->elem_size);

    // Copy element memory content int node element
    memcpy(node->elem, elem, list->elem_size);

    // Set node->next to NULL
    node->next = NULL;

    // Handle case in which head is null
    if(list->head == NULL){
        // Make head point to new node
        list->head = node;
    }

    // Make current tail's next point to node
    list->tail->next = node;

    // Set new node as tail
    list->tail = node;

    // Increase size
    list->size++;
}

void* list_get(linked_list list, const int index){
    struct list_node* n = get_node_at(list, index);

    return n->elem;
}

void list_set(linked_list list, const int index, const void *elem){
    struct list_node* n = get_node_at(list, index);

    // Copy new element memory content onto the old one
    memcpy(n->elem, elem, list->elem_size);
}



void list_remove(linked_list list, const int index){
    struct list_node* n;    // The node to remove

    // Handle head case
    if(index == 0 && list->size > 0){
        n = list->head;
        list->head = list->head->next;
    } else {
        n = get_node_at(list, index-1);
        // Handle tail case
        if(index == list->size - 1){
            list->tail = n;
            n = list->tail->next;
            list->tail->next = NULL;
        } else {
            // Handle normal case, link previous with following node
            struct list_node* to_remove = n->next;
            n->next = to_remove->next;
            n = to_remove;
        }
    }

    // Free node and its element
    free(n->elem);
    free(n);

    // Decrease size
    list->size--;
}

size_t list_size(linked_list list){
    return list->size;
}

