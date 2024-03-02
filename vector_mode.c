#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 4 // max number of threads possible

// structure to pass arguments to the thread function
struct ThreadArgs
{
    int* vector;
    int start;
    int end;
    int* frequencies;
};

// Function to calculate the frequency of the elements in a part of the vector
void* count_frequency(void* arg) {
    // cast the void* arg to the structure with the arguments
    struct ThreadArgs* args = (struct ThreadArgs*) arg;
    for (int i = args->start; i < args->end; i++) {
        // since frequencies is a hashmap, we can access the number and then sum one more to the count of it
        args->frequencies[args->vector[i]]++;
    }
    pthread_exit(NULL);
}

int parallel_mode(int* vector, int vector_size, int num_threads) {
    int frequencies[vector_size];
    memset(frequencies, 0, sizeof(frequencies)); // initialize all element to zero

    // create an array of n threads
    pthread_t threads[num_threads];
    // create an array of n arguments (one for each corresponding thread)
    struct ThreadArgs args[num_threads];

    // create and execute threads
    // to divide the whole vector into several parts (numbers of possible threads)
    // this gives us the size of each part
    int chunk_size = vector_size / num_threads;
    for (int i = 0; i < num_threads; i++) {
        // initialize each part of the structure of arguments
        args[i].vector = vector;
        // move the "pointer" to the next chunk
        args[i].start = i * chunk_size;
        // if the condition is true we are at the end of the vector
        // if not, we move the "pointer" to the end of the current chunk
        args[i].end = (i == num_threads - 1) ? vector_size : (i + 1) * chunk_size;
        args[i].frequencies = frequencies;
        // create/execute the thread
        pthread_create(&threads[i], NULL, count_frequency, (void*) &args[i]);
    }

    // wait until all the threads have finished
    for (int i = 0; i < num_threads; i++) 
        pthread_join(threads[i], NULL);

    // find the element with max frequency
    int max_frequency = 0;
    int mode = -1;
    for (int i = 0; i < vector_size; ++i) {
        if (frequencies[i] > max_frequency) {
            max_frequency = frequencies[i];
            mode = i;
        }
    }

    return mode;
}
