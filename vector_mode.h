#ifndef VECTOR_MODE
#define VECTOR_MODE

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
void* count_frequency(void* arg);


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
int parallel_mode(int* vector, int vector_size, int num_threads);

#endif