#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    auto nums = std::vector<int>(n);
    auto exclusive_prefix_sums = std::vector<long>(n + 1);
    {
        long prev_prefix_sum = 0;
        for (uint i = 0; auto &num : nums) {
            num = read<int>();
            exclusive_prefix_sums[i++] = prev_prefix_sum;
            prev_prefix_sum += num;
        }
        exclusive_prefix_sums[n] = prev_prefix_sum;
    }

    auto max_scores = std::vector<long>(n); // only saving max_scores for prev interval_size
    {
        // initial state
        std::ranges::copy(nums, max_scores.begin());

        // recurrence
        for (auto interval_size : iota(2U, n + 1)) {
            for (auto interval_start : iota(0U, n + 1 - interval_size)) {
                auto interval_sum = exclusive_prefix_sums[interval_start + interval_size] - exclusive_prefix_sums[interval_start];
                max_scores[interval_start] = std::max(
                    interval_sum - max_scores[interval_start + 1], // take the first number
                    interval_sum - max_scores[interval_start]      // take the last number
                );
            }
        }
    }
    std::cout << max_scores[0] << '\n';
}