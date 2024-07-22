// name: <your name here>
// email: <your email here>

#include <stdio.h>

int d[20]; // This array can be used for memoization

long long int dp(int n) {
    // Base cases
    if (n == 0) return 0;
    if (n == 1) return 1;

    // Check if value already computed
    if (d[n] != -1) return d[n];

    // Recursive case with memoization
    d[n] = dp(n - 1) + dp(n - 2);
    return d[n];
}

int main(void) {
    int n;
    scanf("%d", &n);

    // Initialize the memoization array with -1
    for (int i = 0; i < 20; i++) {
        d[i] = -1;
    }

    printf("%lld\n", dp(n));
    return 0;
}
