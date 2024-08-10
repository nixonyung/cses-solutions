#include <algorithm>
#include <cstdio>

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int as[(int)2e5];
    for (int i = 0; i < n; i++) {
        scanf("%d", &as[i]);
    }

    int bs[(int)2e5];
    for (int i = 0; i < m; i++) {
        scanf("%d", &bs[i]);
    }

    // greedy solution: at each step, try to pick the smallest `a` and the smallest `b`

    std::sort(as, as + n);
    std::sort(bs, bs + m);

    int ans = 0;
    int a_idx = 0;
    int b_idx = 0;
    while (a_idx < n && b_idx < m) {
        if (as[a_idx] + k < bs[b_idx]) {
            a_idx++;
        } else if (bs[b_idx] + k < as[a_idx]) {
            b_idx++;
        } else {
            ans++;
            a_idx++;
            b_idx++;
        }
    }
    printf("%d\n", ans);
}