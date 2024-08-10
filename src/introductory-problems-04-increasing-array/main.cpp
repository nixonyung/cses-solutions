#include <algorithm>
#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);

    long ans = 0;
    int curr_max = 0;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);

        curr_max = std::max(curr_max, x);
        ans += curr_max - x;
    }
    printf("%ld\n", ans);
}