#include <algorithm>
#include <climits>
#include <iostream>
#include <set>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    long max_subarray_sum = LONG_MIN;
    {
        decltype(max_subarray_sum) prefix_sum = 0;
        auto prev_prefix_sums = std::multiset<decltype(prefix_sum)>{0};
        decltype(max_subarray_sum) number;
        for (unsigned i = 0; i < N; i++) {
            std::cin >> number;
            prefix_sum += number;
            // subarray_sum(i, j) = prefix_sum[j] - prefix_sum[i-1]
            max_subarray_sum = std::max(max_subarray_sum, prefix_sum - *prev_prefix_sums.begin());
            prev_prefix_sums.insert(prefix_sum);
        }
    }
    std::cout << max_subarray_sum << '\n';
}