#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#define VECTOR_GET(vec, index, type) (*((type*) vector_get(vec, index)))

typedef struct vector vector;  // Struct representing a dynamic array

enum growth_type{
    LINEAR,         // new size = size + growth factor
    EXPONENTIAL     // new size = size * growth factor
};

// Allocates memory and fills vector structure
vector* vector_new(size_t elem_size, size_t init_size);

// Add new element
void vector_add( vector *v, const void* elem);

// Get element at index
void* vector_get( vector *v, const int index);

// Get vector size
size_t vector_size( vector *v);

// Set element at index, returns 0 if set, -1 if error
int vector_set(const vector *v, const int index, const void* elem);

// Removes element at index, shifting back all subsequent elements
int vector_remove(vector *v, const int index);

// Set growth type and factor for this vector
void vector_set_growth(vector* v, const enum growth_type type, const float factor);

// Frees vector memory
void vector_delete(vector *v);


#endif // VECTOR_H
