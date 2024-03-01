#include <stdio.h>
#include "merge_sort.h"
#include "generate_random_numbers.h"

int main() {
    int n = 30;
    int* randomNumbers = generateRandomNumbers(n);

    printf("Given array is \n");
    for (int i = 0; i < n; i++)
        printf("%d ", randomNumbers[i]);
    printf("\n");

    mergeSort(randomNumbers, 0, n - 1);

    printf("Sorted array is \n");
    for (int i = 0; i < n; i++)
        printf("%d ", randomNumbers[i]);
    printf("\n");

    return 0;
}