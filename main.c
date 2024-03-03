#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "merge_sort.h"
#include "generate_random_numbers.h"
#include "clone.h"
#include "parallel_merge_sort.h"
#include "vector_mode.h"

int main() {
    // variables to calculate the time
    clock_t start, end, start2, end2;
    double cpu_time_used, cpu_time_used2;

    // Variables for the generation of the vector and its cone
    int n = 100000;
    int* randomNumbers = generateRandomNumbers(n);
    int* randomNumbersClone = cloneVector(randomNumbers, n);

    // check if the clone vector was successfully created
    if (randomNumbersClone == NULL) {
        printf("Memory allocation failed! Clone vector returned NULL. \n");
        printf("Exiting the program.\n");
        exit(1); 
    }

    // Record the start time for the recursive merge sort
    start = clock();

    // merge sort with recursive implementation
    mergeSort(randomNumbersClone, 0, n - 1);

    // Record the end time for the recursive merge sort
    end = clock();

    // Calculate the CPU time used
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // convert to seconds

    printf("Execution time for the recursive merge sort: %f seconds\n", cpu_time_used);

    // Execution of the parallel merge sort
    int* randomNumbersClone2 = cloneVector(randomNumbers, n);

    // Record the start time for the recursive merge sort
    start2 = clock();

    startParallelSorting(randomNumbersClone2, n);

    // Record the end time for the recursive merge sort
    end2 = clock();

    // Calculate the CPU time used
    cpu_time_used2 = ((double) (end2 - start2)) / CLOCKS_PER_SEC; // convert to seconds

    printf("Execution time for the parallel merge sort: %f seconds\n", cpu_time_used2);

    // Calculate the mode of the sorted vector

    int mode = parallel_mode(randomNumbersClone, n, 4);

    printf("The mode for the sorted vector is %d\n", mode);

    return 0;
}   