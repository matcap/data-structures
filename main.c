#include <stdio.h>
#include "vector.h"
#include <time.h>

typedef struct {
    int i;
    double d;
    char str[6];
} TestStruct;

int main(void)
{
    // Create a vector of MyStructs with initial size of 5
    vector *vec = vector_new(sizeof(TestStruct), 5);

    TestStruct s = {23124, 32132.321, "HELLO\0"};

    // N. of iterations
    const unsigned long iter = 100000000;
    const unsigned long bytes = sizeof(TestStruct) * iter;

    printf("Vector final size: %lu Bytes (%f MB)\n", bytes, (double)(bytes) / (1024.0*1024.0));

    {
        // Start clock
        clock_t start = clock();

        // Perform multiple add()
        for(int i=0; i<iter; i++){
            vector_add(vec, &s);
        }

        // Stop clock
        clock_t end = clock();
        double millis = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;

        printf("\nAddition test: %d additions\n", vector_size(vec));
        printf("Total time: %f ms\n", millis);
        printf("Average time: %f ms\n", millis / (double) iter);
    }

    {
        // Start clock
        clock_t start = clock();

        // Perform multiple remove()
        for(int i=0; i<10; i++){
            vector_remove(vec, 0);
        }

        // Stop clock
        clock_t end = clock();
        double millis = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;

        printf("\nRemove test: %d removals\n", iter);
        printf("Total time: %f ms\n", millis);
        printf("Average time: %f ms\n", millis / (double) iter);
    }



    vector_delete(vec);
    return 0;
}

