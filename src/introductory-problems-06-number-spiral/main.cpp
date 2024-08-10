#include <algorithm>
#include <cstdio>

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int x, y;
        scanf("%d %d", &y, &x);

        long ans;
        int layer_idx = std::max(x, y);
        if (layer_idx & 1) {
            // the largest element (layer_idx^2) is at top-right
            ans = (long)layer_idx * layer_idx + (1 - y) + (x - layer_idx);
        } else {
            // the largest element (layer_idx^2) is at bottom-left
            ans = (long)layer_idx * layer_idx + (y - layer_idx) + (1 - x);
        }
        printf("%ld\n", ans);
    }
}