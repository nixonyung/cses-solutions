#include <algorithm>
#include <cstdio>

int main() {
    int n, x;
    scanf("%d %d", &n, &x);

    int ps[(int)2e5];
    for (int i = 0; i < n; i++) {
        scanf("%d", &ps[i]);
    }

    // greedy solution: at each step, try to pick the smallest `p` and the largest `p`

    std::sort(ps, ps + n);

    int ans = 0;
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        if (ps[left] + ps[right] <= x) {
            left++;
            right--;
        } else {
            right--;
        }
        ans++;
    }
    printf("%d\n", ans);
}