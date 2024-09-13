#include "utils.hpp"
#include <set>

int main() {
    enable_fast_io();

    auto n = read<uint>();

    long max_subarray_sum = std::numeric_limits<long>::min();
    {
        long curr_prefix_sum = 0;
        auto prefix_sums_set = std::multiset<long>{0};
        {
            for (auto _ : iota(0U, n)) {
                curr_prefix_sum += read<int>();
                max_subarray_sum = std::max(max_subarray_sum, curr_prefix_sum - *prefix_sums_set.begin());
                prefix_sums_set.insert(curr_prefix_sum);
            }
        }
    }
    std::cout << max_subarray_sum << '\n';
}