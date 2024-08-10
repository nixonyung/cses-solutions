#include <algorithm>
#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);

    /*
    implementations that won't work:
        - store counters for all a,b
            => a,b <= 1e9 is too large
    */
    int as[(int)2e5];
    int bs[(int)2e5];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &as[i], &bs[i]);
    }

    // direct implementation of the problem using pointers

    std::sort(as, as + n);
    std::sort(bs, bs + n);

    int ans = 0;
    int curr_num = 0;
    int a_idx = 0;
    int b_idx = 0;
    while (a_idx < n) {
        if (as[a_idx] < bs[b_idx]) {
            curr_num++;
            ans = std::max(ans, curr_num);
            a_idx++;
        } else if (as[a_idx] < bs[b_idx]) {
            curr_num--;
            b_idx++;
        } else {
            a_idx++;
            b_idx++;
        }
    }
    // there maybe bs not yet processed, but they can be skipped as processing them
    // will only decrement curr_num and thus will not change ans
    printf("%d\n", ans);
}