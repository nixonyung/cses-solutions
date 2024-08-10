#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);

    // (ref.) [CSES Solutions - Two Knights](https://www.geeksforgeeks.org/cses-solutions-two-knights/)
    for (int k = 1; k <= n; k++) {
        // choose 2 cells from the board, order doesn't matter
        long num_total = (long)k * k * (k * k - 1) / 2;
        // 2 invalid configurations for each 2x3 and 3x2 cells
        long num_invalid = (long)(k - 1) * (k - 2) * 4;

        printf("%ld\n", num_total - num_invalid);
    }
}