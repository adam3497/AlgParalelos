#include <stdio.h>
#include <stdlib.h>

#include "merge_sort.h"
#include "generate_random_numbers.h"
#include "clone.h"

int main() {
    int n = 30;
    int* randomNumbers = generateRandomNumbers(n);
    int* randomNumbersClone = cloneVector(randomNumbers, n);

    // check if the clone vector was successfully created
    if (randomNumbersClone == NULL) {
        printf("Memory allocation failed! Clone vector returned NULL. \n");
        printf("Exiting the program.\n");
        exit(1); 
    }

    printf("Given array is \n");
    for (int i = 0; i < n; i++)
        printf("%d ", randomNumbersClone[i]);
    printf("\n");

    mergeSort(randomNumbersClone, 0, n - 1);

    printf("Sorted array is \n");
    for (int i = 0; i < n; i++)
        printf("%d ", randomNumbersClone[i]);
    printf("\n");

    return 0;
}