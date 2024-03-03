#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "vector_mode.h"

#define NUM_THREADS 4 // max number of threads possible

/**
 * Structure containing arguments for the count_frequency function.
 * 
 * This structure is used to pass arguments to the count_frequency function
 * when executing it in parallel threads. It includes a pointer to the integer
 * vector, the start and end indices of the portion of the vector to process,
 * and a pointer to an array to store the frequencies of elements.
 */
struct ThreadArgs
{
    int* vector;
    int start;
    int end;
    int* frequencies;
};

/**
 * Counts the frequency of each element in a portion of an integer vector.
 * 
 * This function is used by the parallel_mode function to count the frequency
 * of each element in a portion of the integer vector. It is executed by each
 * thread in parallel to process a specific range of elements within the vector.
 * 
 * @param arg Pointer to the ThreadArgs structure containing arguments for the
 *            function, including the integer vector, start index, end index,
 *            and array to store the frequencies.
 * 
 * @return None.
 */
void* count_frequency(void* arg) {
    // cast the void* arg to the structure with the arguments
    struct ThreadArgs* args = (struct ThreadArgs*) arg;

    // Since we are working with negative values in the vector
    // we need to put an offset for the frequencies index, to avoid any error
    // the range of the value is [-1000, 1000] so an offset of 1000 would be enough
    int offset = 1000;

    for (int i = args->start; i < args->end; i++) {
        // calculate the adjusted index by adding the offset
        int index = args->vector[i] + offset;

        // incremente the count at the adjusted index
        args->frequencies[index]++;
    }
    pthread_exit(NULL);
}

/**
 * Calculates the mode of a given integer vector in parallel.
 * 
 * This function computes the mode (most frequently occurring value) of the
 * provided integer vector using a parallelized approach. It divides the vector
 * into chunks and utilizes multiple threads to count the frequency of each
 * element concurrently. The mode is determined by finding the value with the
 * highest frequency across all chunks.
 * 
 * @param vector      Pointer to the integer vector to compute the mode for.
 * @param vector_size Size of the integer vector.
 * @param num_threads Number of threads to use for parallel processing.
 * 
 * @return The mode of the integer vector.
 */
int parallel_mode(int* vector, int vector_size, int num_threads) {
    int frequencies[2001]; // Adjusted size of frequencies array
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
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
        
    // find the element with max frequency
    int max_frequency = 0;
    int mode = -1;
    int offset = 1000;
    for (int i = 0; i < 2001; ++i) {
        if (frequencies[i] > max_frequency) {
            max_frequency = frequencies[i];
            mode = i - offset;
        }
    }

    return mode;
}