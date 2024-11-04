// (ref.) [CSES - Maximum Subarray II](https://usaco.guide/problems/cses-1644-max-subarray-sum-ii/solution)

#include <climits>
#include <iostream>
#include <set>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned MIN_SUBARRAY_LENGTH;
    unsigned MAX_SUBARRAY_LENGTH;
    {
        std::cin >> N >> MIN_SUBARRAY_LENGTH >> MAX_SUBARRAY_LENGTH;
    }

    long max_subarray_sum = LONG_MIN;
    {
        auto prefix_sums = std::vector<long>(N);
        auto s = std::multiset<decltype(prefix_sums)::value_type>(); // prev prefix_sums that should be considered
        int number;
        for (unsigned i = 0; i < N; i++) {
            std::cin >> number;

            prefix_sums[i] = ((i != 0) ? prefix_sums[i - 1] : 0) + number;

            auto const len = i + 1;
            if (len >= MIN_SUBARRAY_LENGTH && len <= MAX_SUBARRAY_LENGTH) {
                max_subarray_sum = std::max(max_subarray_sum, prefix_sums[i]);
            }
            if (len > MIN_SUBARRAY_LENGTH) {
                s.insert(prefix_sums[i - MIN_SUBARRAY_LENGTH]);
                max_subarray_sum = std::max(max_subarray_sum, prefix_sums[i] - *s.begin());
            }
            if (len > MAX_SUBARRAY_LENGTH) {
                s.extract(prefix_sums[i - MAX_SUBARRAY_LENGTH]);
            }
        }
    }
    std::cout << max_subarray_sum << '\n';
}