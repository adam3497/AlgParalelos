#include <stdlib.h>
#include <pthread.h>

#include "parallel_merge_sort.h"

#define MAX_THREADS 8

// Global variable to track the number of active threads
int active_threads = 0;
pthread_mutex_t mutex;

// Merge two sorted sub-arrays into one sorted array
void merge_(int arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary arrays to hold the left and right sub-arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Sequential merge sort
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        // split the array into two sub-arrays 
        merge_sort(arr, left, middle);
        merge_sort(arr, middle + 1, right);
        // merge back the two sub-arrays into the original array
        merge_(arr, left, middle, right);
    }
}

// Threaded merge sort with limited number of threads
void *threaded_merge_sort(void *args) {
    // get the arguments passed into the function using the *args struct
    struct Params *params = (struct Params *)args;
    int left = params->left;
    int right = params->right;
    int *arr = params->arr;

    if (left < right) {
        int middle = left + (right - left) / 2;

        // Create two threads for sorting each half if the number of active threads is less than MAX_THREADS
        pthread_t tid1, tid2;
        struct Params params1 = { arr, left, middle };
        struct Params params2 = { arr, middle + 1, right };

        // lock the mutex
        pthread_mutex_lock(&mutex);
        // check if the active threads is less than the max threads 
        if (active_threads < MAX_THREADS) {
            active_threads += 2; // two new threads for both halves
            // create both threads and call the corresponding function with their arguments
            pthread_create(&tid1, NULL, threaded_merge_sort, &params1);
            pthread_create(&tid2, NULL, threaded_merge_sort, &params2);
        } else {
            // we reach the max numbers of threads
            pthread_mutex_unlock(&mutex);
            // If the maximum number of threads is reached, resort to sequential sorting
            merge_sort(arr, left, middle);
            merge_sort(arr, middle + 1, right);
            merge_(arr, left, middle, right);
            pthread_exit(NULL);
        }
        // unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Wait for the threads to finish
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        // Merge the sorted halves
        merge_(arr, left, middle, right);
    }

    // since active_threads is a shared memory variable, we want to lock the mutex
    pthread_mutex_lock(&mutex);
    active_threads--;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

// start of the parallel merge sort functionality 
void startParallelSorting(int arr[], int n) {

    // create the initial arguments
    struct Params params = { arr, 0, n - 1 };

    // initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // create the first thread that control the first merge sorting process
    pthread_t tid;
    
    // start the merge sort
    pthread_create(&tid, NULL, threaded_merge_sort, &params);

    // wait until the thread finishes 
    pthread_join(tid, NULL);

    // one is finished, destroy the mutex
    pthread_mutex_destroy(&mutex);
}
