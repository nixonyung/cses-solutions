#include <algorithm>
#include <cstdio>
#include <cstdlib>

int main() {
    int n;
    scanf("%d", &n);

    int ps[(int)2e5];
    for (int i = 0; i < n; i++) {
        scanf("%d", &ps[i]);
    }

    /*
    solution: use median as the target length
        if n is odd:
            choose p[n/2]
        if n is even:
            choose either p[n/2] or p[n/2 + 1]
            (p[n/2] is chosen here)
    */

    std::sort(ps, ps + n);
    int median = ps[n >> 1];

    long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += abs(ps[i] - median);
    }
    printf("%ld\n", ans);
}