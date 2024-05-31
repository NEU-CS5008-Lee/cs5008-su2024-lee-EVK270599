//Kaustubha Eluri
//eluri.k@northeastern.edu

//To perform insertion sort of integers stored in a file and display the output and store it in another file.
#include <stdio.h>
#include<stdlib.h>

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main()
{
    FILE *fp;
    int arr[10];
    int count = 0, i;
    /*count will have the total number of elements in the array*/

    /*read the file*/
    fp = fopen("Input1.txt", "r");
    if (fp == NULL) {
        //if file returns NULL then can't open the file
        printf("\n Cannot open the file \n");
        exit(0);
    }
    
    // Read integers from the file into the array
    while (fscanf(fp, "%d", &arr[count]) != EOF) {
        count++;
    }
    fclose(fp);

    // Perform insertion sort
    insertionSort(arr, count);

    // Display sorted array
    printf("Sorted array: \n");
    for (i = 0; i < count; i++) {
        printf("%d\n", arr[i]);
    }

    // Write sorted array to output file
    fp = fopen("sorted.txt", "w");
    if (fp == NULL) {
        printf("\n Cannot open the file \n");
        exit(0);
    }
    for (i = 0; i < count; i++) {
        fprintf(fp, "%d\n", arr[i]);
    }
    fclose(fp);

    return 0;
}