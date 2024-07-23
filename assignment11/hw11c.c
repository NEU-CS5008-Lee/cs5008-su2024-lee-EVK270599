// name: Kaustubha Eluri
// email: eluri.k@northeastern.edu

#include <stdio.h>

int d[21];  // The array size is 21 to accommodate D[20]

long long int dp(int n) {
    if (n == 0) return 1;
    if (n == 1) return 0;
    if (n == 2) return 3;
    if (d[n] != -1) return d[n];

    long long int result = 3 * dp(n - 2);
    for (int i = 4; i <= n; i += 2) {
        result += 2 * dp(n - i);
    }

    d[n] = result;
    return result;
}

int main(void) {
    int n;
    for (int i = 0; i <= 20; i++) {
        d[i] = -1;
    }
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
