#include <cstdio>

int main() {
    int MOD = (int)1e9 + 7;

    int n;
    scanf("%d", &n);

    // ans = 2^n
    // (ref.) [Binary Exponentiation](https://cp-algorithms.com/algebra/binary-exp.html)
    long ans = 1;
    long step = 2;
    while (n > 0) {
        if (n & 1) {
            ans = (ans * step) % MOD;
        }
        step = (step * step) % MOD;
        n >>= 1;
    }
    printf("%ld\n", ans);
}