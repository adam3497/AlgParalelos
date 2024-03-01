#ifndef MERGE_SORT
#define MERGE_SORT

// Function to merge 2 sub-arrays
// First: arr[1..m]
// Second: arr[m+1..r]
void merge(int arr[], int l, int m, int r);

// Recursive merge sort function
void mergeSort(int arr[], int l, int r);

#endif /* MERGE_SORT*/