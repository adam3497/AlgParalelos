#include <stdlib.h>
#include "clone.h"

/* Function to clone the vector */
void* cloneVector(int arr[], int size) {
    // allocate memory for the new vector
    int* clone = (int*)malloc(size * sizeof(int));

    // check if memory allocation was successful
    if (clone == NULL) {
        return NULL; // exit the program
    }

    // copy elements from the original vector to the new one
    for (int i = 0; i < size; i++){
        clone[i] = arr[i];
    }

    return clone;
}