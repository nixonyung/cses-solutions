#include <algorithm>
#include <cstdio>

int delta(
    int a,
    int b,
    int xs[],
    int pos[]) {
    if (xs[a] + 1 == xs[b]) {
        return (pos[xs[a] - 1] > a) +
               (a > b) +
               (b > pos[xs[b] + 1]);
    } else if (xs[b] + 1 == xs[a]) {
        return (pos[xs[b] - 1] > b) +
               (b > a) +
               (a > pos[xs[a] + 1]);
    } else {
        return (pos[xs[a] - 1] > a) + (a > pos[xs[a] + 1]) +
               (pos[xs[b] - 1] > b) + (b > pos[xs[b] + 1]);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int xs[(int)2e5 + 1];  // xs[1] is the first appeared x
    int pos[(int)2e5 + 2]; // pos[x] is the position of x, first appeared x has pos[x] = 1
    /*
    side properties:
        - xs[pos[x]] = x
        - pos[xs[i]] = i
    */

    for (int i = 1; i <= n; i++) {
        scanf("%d", &xs[i]);
        pos[xs[i]] = i;
    }
    // dummy values to handle index-out-of-bound
    pos[0] = 0;
    pos[n + 1] = n + 1;

    // ans is the number of increasing subsequence in `pos`
    int ans = 1;
    for (int i = 1; i <= n - 1; i++) {
        if (pos[i] > pos[i + 1]) {
            ans++;
        }
    }

    while (m--) {
        int a, b;
        scanf("%d %d", &a, &b);

        // for each swap, update ans only by the delta contributed by index a and b
        ans -= delta(a, b, xs, pos);
        std::swap(pos[xs[a]], pos[xs[b]]);
        std::swap(xs[a], xs[b]);
        ans += delta(a, b, xs, pos);
        printf("%d\n", ans);
    }
}