#include "merge_sort.h"

// Function to merge 2 sub-arrays
// First: arr[1..m]
// Second: arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    // Calculate the length of both sub-arrays
    int n1 = m - l + 1;
    int n2 = r - m;

    // create temp arrays of size n1 and n2
    int L[n1], R[n2];

    // copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // merge both temp arrays back into arr[l..r] (original)
    i = 0;
    j = 0;
    k = l;
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

    // copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Recursive merge sort function
void mergeSort(int arr[], int l, int r) {
    int m; 
    
    if (l < r) {
        // find the middle point
        m = l + (r - l) / 2; 

        // sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // merge sorted halves
        merge(arr, l, m, r);
    }
}