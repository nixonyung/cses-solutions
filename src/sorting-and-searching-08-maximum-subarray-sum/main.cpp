#include <algorithm>
#include <climits>
#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);

    long ans = LONG_MIN;
    long curr_sum = 0;
    while (n--) {
        int x;
        scanf("%d", &x);

        curr_sum += x;
        ans = std::max(ans, curr_sum);
        /*
        if curr_sum > 0:
            keep curr_sum, as it may constitute to a larger subarray sum
        else:
            reset curr_sum, as a negative curr_sum will only make the subarray sum smaller
        */
        curr_sum = (curr_sum > 0) ? curr_sum : 0;
    }
    printf("%ld\n", ans);
}