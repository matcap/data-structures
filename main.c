#include <stdio.h>
#include "vector/vector.h"
#include "list/linked_list.h"

typedef struct {
    int index;
    char value[8];
} data;

// Common data array
static data arr[] = {
    {0, "Data 0"},
    {1, "Data 1"},
    {2, "Data 2"},
    {3, "Data 3"},
    {4, "Data 4"}
};

// Custom free function
void free_data(void* elem){
    data* d = (data*) elem;
    printf("Deleted {%d, %s}\n", d->index, d->value);
}


/*
 *  #################### VECTOR ####################
 */
void vector_example(){
    printf("\nVECTOR\n");

    // Create a vector of data with initial size of 2
    vector vec = vector_new(sizeof(data), 1, free_data);

    // Add each data to our vector
    for(int i=0; i<5; i++){
        vector_add(vec, &arr[i]);
    }

    // Change one of our values to something different
    data newdata = {6, "Data 6"};
    vector_set(vec, 2, &newdata);

    // Remove one element
    vector_remove(vec, 3);

    // Print vector to screen
    for(int i=0; i<vector_size(vec); i++){
        // Get each element using explicit casts
        data elem = *((data*) vector_get(vec, i));
        // Or use the more readable macro
        elem = VECTOR_GET(vec, i, data);

        printf("Vector[%d] = {%d, %s}\n", i, elem.index, elem.value);
    }

    // Free memory
    vector_delete(vec);
}

/*
 *  #################### LINKED LIST ####################
 */
void linked_list_example(){
    printf("\nLINKED LIST\n");



    // Allocate a new list
    linked_list list = list_new(sizeof(data), free_data);

    // Add to list head each data
    for(int i=0; i<5; i++){
        list_add_head(list, &arr[i]);
    }

    // Add to list tail each data
    for(int i=0; i<5; i++){
        list_add_tail(list, &arr[i]);
    }

    // Modify an existing list element
    data newdata = {6, "Data 6"};
    list_set(list, list_size(list) - 2, &newdata);

    // Remove existing list node
    list_remove(list, 4);
    list_remove(list, 4);

    // Iterate over list elements
    for(int i=0; i < list_size(list); i++ ){
        // Get data
        data elem = *((data*) list_get(list, i));

        printf("Vector[%d] = {%d, %s}\n", i, elem.index, elem.value);
    }

    // Free memory
    list_delete(list);
}




int main(void){

    vector_example();

    linked_list_example();

    return 0;
}

