#include <cstdio>

int main() {
    long n;
    scanf("%ld", &n);
    printf("%ld ", n);

    while (n != 1) {
        n = (n & 1) ? (n * 3 + 1) : (n >> 1);
        printf("%ld ", n);
    }
    printf("\n");
}