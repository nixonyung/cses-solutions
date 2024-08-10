#include <algorithm>
#include <cmath>
#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);

    int ps[20];
    long sum1 = 0;
    long sum2 = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &ps[i]);
        sum1 += ps[i];
    }

    /*
    solve by enumerating all possible bitmasks:
        for the k-th bit in the bitmask, if the bit == 0, assign pk to group 1, else to group 2
    */
    long ans = sum1;
    int bitmask = 0;
    // using "iterative Gray code" as an optimization
    for (int i = 1; i < (1 << n) - 1; i++) {
        int p_idx = __builtin_ctz(i);
        bitmask ^= 1 << p_idx;
        if (bitmask & (1 << p_idx)) {
            sum2 += ps[p_idx];
            sum1 -= ps[p_idx];
        } else {
            sum1 += ps[p_idx];
            sum2 -= ps[p_idx];
        }
        ans = std::min(ans, abs(sum1 - sum2));
    }
    printf("%ld\n", ans);
}
