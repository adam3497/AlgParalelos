#include <stdlib.h>
#include <time.h>
#include "generate_random_numbers.h"

// Function to generate random numbers between -1000 and 1000.
// It receives an int number n
// It returns the result in a vector of size n
int* generateRandomNumbers(int n) {
    int* numbers = (int*)malloc(n * sizeof(int));
    
    // generate a random seed
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        // Generate a random number between -1000 and 1000
        int random_number = rand() % 2001 - 1000;
        numbers[i] = random_number;
    }

    return numbers;
}