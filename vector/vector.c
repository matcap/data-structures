#include "vector.h"

#include <stdlib.h>
#include <memory.h>

#define ABS(a)      ((a > 0) ? a : -a)
#define MAX(a,b)    ((a >= b) ? a : b)

#define MIN_VEC_SIZE    2
#define GROWTH_FACTOR   1.5

struct vector_s{
    size_t elem_size;           // Size of a single element
    size_t size;                // Physical number of elements allocated
    size_t used;                // Logical number of elements used
    free_fun fun;               // Custom free function
    void* base;                 // Vector base pointer
};

vector vector_new(size_t elem_size, size_t init_size, free_fun fun){

    // Allocate memory for vector struct
    vector  v = malloc(sizeof(struct vector_s));

    // Allocate memory for 2 elements
    init_size =  MAX( MIN_VEC_SIZE, init_size );
    v->base = malloc(elem_size * init_size);

    // Return NULL if malloc returned a null pointer
    if(!v->base){
        return NULL;
    }

    // Set vector fields
    v->elem_size = elem_size;
    v->size = init_size;
    v->used = 0;
    v->fun = fun;

    return v;
}

void vector_delete(vector v){

    // Delete elements
    if(v->fun != NULL)
        for(int i=0; i<v->used; i++){
            v->fun(vector_get(v, i));
        }

    // Free allocated memory
    if(v){
        if(v->base)
            free(v->base);
        free(v);
    }
}


void vector_add(vector v, const void *elem){
    // Check if vector needs to be resized
    if(v->used >= v->size){
        // Increase by growth factor
        v->size = (size_t) (v->size * GROWTH_FACTOR);

        // Reallocate memory
        void* newbase = realloc(v->base, v->size * v->elem_size);
        if(!newbase){
            // Deallocate original
            free(v->base);
            return;
        }
        v->base = newbase;
    }

    // Add element to vector
    memcpy(((char*)v->base + v->elem_size * v->used), elem, v->elem_size);
    v->used++;
}



void* vector_get(const vector v, int index){
    return ((char*)v->base + v->elem_size * index);
}


size_t vector_size( vector v){
    return v->used;
}


int vector_set(const vector v, const int index, const void *elem){
    // Return error if index is greater than last element index
    if(index >= v->used)
        return 0;

    // Copy element into vector[index]
    memcpy(((char*)v->base + v->elem_size * index), elem, v->elem_size);
    return 1;
}


int vector_remove(vector v, const int index){
    // Free element at index
    if(v->fun != NULL)
        v->fun(vector_get(v, index));

    // Shift back all the elements after index
    if(index < v->used-1){
        memmove(((char*)v->base + v->elem_size * index),
               ((char*)v->base + v->elem_size * (index + 1)),
               v->elem_size * (v->used - index - 1));
    }
    // Decrease used
    v->used--;

    // Check if size needs to be reduced
    if(v->used < v->size / GROWTH_FACTOR){
        // Reduce by growth factor
        v->size = (size_t) (v->size / GROWTH_FACTOR);

        // Reallocate to a smaller size
        void* newbase = (void*) realloc(v->base, v->size * v->elem_size);
        if(newbase)
            v->base = newbase;
        else
            return 0;
    }

    return 1;
}
