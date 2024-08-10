#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);

    int xorsum = 0;
    for (int i = 1; i <= n; i++) {
        xorsum ^= i;
    }

    for (int i = 0; i < n - 1; i++) {
        int x;
        scanf("%d", &x);
        xorsum ^= x;
    }
    printf("%d\n", xorsum);
}