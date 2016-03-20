#include <stdio.h>
#include "vector/vector.h"
#include <time.h>

typedef struct {
    int index;
    char value[10];
} data;


/*
 *  #################### VECTOR ####################
 */
void vector_example(){
    // Create a vector of data with initial size of 2
    vector* vec = vector_new(sizeof(data), 2);

    // Create an array of data
    data arr[] = {
        {1, "Data 1"},
        {2, "Data 2"},
        {3, "Data 3"},
        {4, "Data 4"},
        {5, "Data 5"}
    };

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




int main(void)
{
    vector_example();
    return 0;
}

