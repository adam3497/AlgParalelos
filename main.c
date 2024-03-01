#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "merge_sort.h"
#include "generate_random_numbers.h"
#include "clone.h"

int main() {
    // variables to calculate the time
    clock_t start, end;
    double cpu_time_used;

    // Variables for the generation of the vector and its cone
    int n = 500000;
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
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // convert to nanoseconds

    /* printf("Given array is \n");
    for (int i = 0; i < n; i++)
        printf("%d ", randomNumbers[i]);
    printf("\n");

    printf("Sorted array is \n");
    for (int i = 0; i < n; i++)
        printf("%d ", randomNumbersClone[i]);
    printf("\n"); */

    printf("Execution time for the recursive merge sort: %f seconds\n", cpu_time_used);

    return 0;
}   