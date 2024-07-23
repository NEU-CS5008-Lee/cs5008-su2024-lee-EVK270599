// name: Kaustubha Eluri
// email: eluri.k@northeastern.edu

#include <stdio.h>

long long int d[21]; // Initialize an array to store the results

long long int dp(int n) {
    if (n == 0) return 1; // Base case: 1 way to tile a 2 x 0 floor
    if (n == 1) return 1; // Base case: 1 way to tile a 2 x 1 floor

    if (d[n] != 0) return d[n]; // Use memoization to return already computed results

    // The recurrence relation: D[i] = D[i - 1] + D[i - 2]
    d[n] = dp(n - 1) + dp(n - 2);

    return d[n];
}

int main(void) {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    if (n < 0 || n > 20) {
        printf("Please enter a number between 0 and 20.\n");
        return 1;
    }

    printf("The number of ways to tile a 2 x %d floor is %lld\n", n, dp(n));
    return 0;
}
