#include <cstdio>

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int a, b;
        scanf("%d %d", &a, &b);

        // as each move remove 3 coins, for cases where all coins can be removed,
        // the total number of coins must be a multiple of 3
        if ((a + b) % 3) {
            printf("NO\n");
            continue;
        }
        // there exists a solution iff the size of the larger pile is at most twice the size of the smaller pile
        if ((a > b * 2) || (b > a * 2)) {
            printf("NO\n");
            continue;
        }
        printf("YES\n");
    }
}