#include "vector.h"

#include <stdlib.h>
#include <memory.h>

#define ABS(a)      ((a > 0) ? a : -a)
#define MAX(a,b)    ((a >= b) ? a : b)

#define MIN_VEC_SIZE 2

struct vector{
    void* base;                 // Vector base pointer
    size_t elem_size;           // Size of a single element
    size_t size;                // Physical number of elements allocated
    size_t used;                // Logical number of elements used
    enum growth_type growth;    // Growth type
    float growth_factor;        // Growth factor
    //float growth_threshold;     // Threshold above which vector should be resized
};

vector *vector_new(size_t elem_size, size_t init_size){

    // Allocate memory for vector struct
    vector* v = (vector*) malloc(sizeof(vector));

    // Allocate memory for 2 elements
    init_size =  MAX( MIN_VEC_SIZE, init_size );
    v->base = (void*) malloc(elem_size * init_size);

    // Return NULL if malloc returned a null pointer
    if(!v->base){
        return NULL;
    }

    // Set vector fields
    v->elem_size = elem_size;
    v->size = init_size;
    v->used = 0;

    // Defalut vector growth is exponential by a factor of 2 (new size = size^2)
    v->growth = EXPONENTIAL;
    v->growth_factor = 1.5;

    return v;
}

void vector_delete( vector *v){
    // Free allocated memory
    if(v){
        if(v->base)
            free(v->base);
        free(v);
    }
}


void vector_add( vector *v, const void *elem){
    // Check if vector needs to be resized
    if(v->used >= v->size){
        // Resize based on growth type
        if(v->growth = LINEAR)
            v->size = (size_t) (v->size + v->growth_factor);
         else
            v->size = (size_t) (v->size * v->growth_factor);
        // Reallocate memory
        void* newbase = (void*) realloc(v->base, v->size * v->elem_size);
        if(newbase)
            v->base = newbase;
        else
            return;
    }

    // Add element to vector
    memcpy((v->base + v->elem_size * v->used), elem, v->elem_size);
    v->used++;
}



void* vector_get( vector *v, int index){
    return (v->base + v->elem_size * index);
}


size_t vector_size( vector *v){
    return v->used;
}


int vector_set(const vector *v, const int index, const void *elem){
    // Return error if index is greater than last element index
    if(index >= v->used)
        return 0;

    // Copy element into vector[index]
    memcpy((v->base + v->elem_size * index), elem, v->elem_size);
    return 1;
}


int vector_remove(vector *v, const int index){
    // Shift back all the elements after index
    if(index < v->used-1){
        memmove((v->base + v->elem_size * index),
               (v->base + v->elem_size * (index + 1)),
               v->elem_size * (v->used - index - 1));
    }
    // Decrease used
    v->used--;

    // Check if size needs to be reduced
    if(v->used < v->size / v->growth_factor){
        // Resize based on growth type
        if(v->growth = LINEAR)
            v->size = (size_t) (v->size - v->growth_factor);
         else
            v->size = (size_t) (v->size / v->growth_factor);

        // Reallocate to a smaller size
        void* newbase = (void*) realloc(v->base, v->size * v->elem_size);
        if(newbase)
            v->base = newbase;
        else
            return 0;
    }
}


void vector_set_growth(vector* v, const enum growth_type type, const float factor){
    v->growth = type;
    v->growth_factor = factor;
}
