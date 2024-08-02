//eluri.k@northeastern.edu
//Kaustubha Eluri

#include<stdio.h>
#include<string.h>

int compression(char arr[], int n, char res[]){
    int i, j = 0;
    for (i = 0; i < n; i++) {
        int count = 1;
        // Count occurrences of the current character
        while (i < n - 1 && arr[i] == arr[i + 1]) {
            count++;
            i++;
        }
        // Append current character and its count to the result string
        res[j++] = arr[i];
        j += sprintf(&res[j], "%d", count);
    }
    res[j] = '\0'; // Null-terminate the result string
    return j; // Return the length of the compressed string
}
 
int main() {
    char a[] = "aaaaaaaaaaaaaabbbbcccd";
    char res[50];
    int r, n = strlen(a); // n is the size of input array
    r = compression(a, n, res);
    printf("Compressed string: %s\n", res);
    printf("Length of the compressed string: %d\n", r);
    return 0;
}
