// (ref.) [Longest increasing subsequence](https://www.wikiwand.com/en/articles/Longest_increasing_subsequence#Efficient_algorithms)

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    unsigned max_subarray_len = 0;
    {
        auto len_to_min_ending_number = std::vector<unsigned>(N, -1U);
        {
            len_to_min_ending_number[0] = 0;

            unsigned number;
            for (unsigned i = 0; i < N; i++) {
                std::cin >> number;

                /*
                We want to find the largest `len` where the corresponding `ending_number` < `number`,
                then update len_to_min_ending_number[len+1] = number.

                optimization: finding `len+1` is equivalent to finding the smallest `len2` where the corresponding `ending_number` >= `number`
                optimization: len_to_min_ending_number must be an increasing sequence, so we can use binary search
                */
                auto it = std::ranges::lower_bound(len_to_min_ending_number, number);
                *it = number;
                max_subarray_len = std::max(max_subarray_len, (unsigned)(it - len_to_min_ending_number.begin()));
            }
        }
    }
    std::cout << max_subarray_len << '\n';
}