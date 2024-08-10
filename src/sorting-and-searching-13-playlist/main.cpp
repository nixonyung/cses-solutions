#include <algorithm>
#include <cstdio>
#include <map>

int main() {
    int n;
    scanf("%d", &n);

    int ans = 0;
    std::unordered_map<int, int> m;
    int left = 0;
    for (int right = 0; right < n; right++) {
        int k;
        scanf("%d", &k);

        // update left to the smallest index where there are no duplicates in [left, right]
        if (m.contains(k)) {
            left = std::max(left, m[k] + 1);
        }
        ans = std::max(ans, right - left + 1);
        m[k] = right;
    }
    printf("%d\n", ans);
}