#include "utils.hpp"
#include <set>

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto min_length = read<uint>();
    auto max_length = read<uint>();

    // (ref.) [CSES - Maximum Subarray II](https://usaco.guide/problems/cses-1644-max-subarray-sum-ii/solution)

    long max_subarray_sum = std::numeric_limits<long>::min();
    {
        auto prefix_sums = std::vector<long>(n);
        auto prefix_sums_set = std::multiset<long>();
        long curr_prefix_sum = 0;
        for (auto i : iota(0U, n)) {
            curr_prefix_sum += read<int>();
            prefix_sums[i] = curr_prefix_sum;
            if (i + 1 >= min_length) {
                prefix_sums_set.insert(
                    (i + 1 == min_length) ? 0 // 0 means "don't remove from curr_prefix_sum"
                                          : prefix_sums[i - min_length]
                );
                max_subarray_sum = std::max(max_subarray_sum, curr_prefix_sum - *prefix_sums_set.begin());
            }
            if (i + 1 >= max_length) {
                prefix_sums_set.extract(
                    (i + 1 == max_length) ? 0
                                          : prefix_sums[i - max_length]
                );
            }
        }
    }
    std::cout << max_subarray_sum << '\n';
}