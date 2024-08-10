#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);

    int pos[(int)2e5 + 1]; // pos[x] is the position of x, first appeared x has pos[x] = 0
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        pos[x] = i;
    }

    // ans is the number of increasing subsequence in `pos`
    int ans = 1;
    for (int i = 1; i <= n - 1; i++) {
        if (pos[i] > pos[i + 1]) {
            ans++;
        }
    }
    printf("%d\n", ans);
}