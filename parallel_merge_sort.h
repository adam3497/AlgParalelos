#ifndef PARALLEL_MERGE_SORT
#define PARALLEL_MERGE_SORT

// Structure to pass parameters to the sorting function
struct Params {
    int *arr;
    int left;
    int right;
};

// Merge two sorted sub-arrays into one sorted array
void merge_(int arr[], int left, int middle, int right);

// Sequential merge sort
void merge_sort(int arr[], int left, int right);

// Threaded merge sort with limited number of threads
void *threaded_merge_sort(void *args);

// start of the parallel merge sort functionality 
void startParallelSorting(int arr[], int n);

#endif /* PARALLEL_MERGE_SORT */