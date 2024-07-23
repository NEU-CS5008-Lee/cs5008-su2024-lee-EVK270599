// name: Kaustubha Eluri
// email: eluri.k@northeastern.edu

#include <stdio.h>

int d[20];

long long int dp(int n) {
    
    if (n == 1) return 1;
    if (n == 2) return 3;

    d[1] = 1;
    d[2] = 3;

    for (int i = 3; i <= n; ++i) {
        d[i] = d[i-1] + 2 * d[i-2];
    }

    return d[n];
}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
    return 0;
}
