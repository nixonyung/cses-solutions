#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    auto max_subarray_sum = std::numeric_limits<long>::min();
    {
        long curr_sum = 0;
        while (n--) {
            curr_sum += read<int>();
            max_subarray_sum = std::max(max_subarray_sum, curr_sum);
            /*
            if curr_sum > 0:
                keep curr_sum, as it may constitute to a larger subarray sum
            else:
                reset curr_sum, as a negative curr_sum will only make the subarray sum smaller
            */
            curr_sum = std::max(curr_sum, 0L);
        }
    }
    std::cout << max_subarray_sum << '\n';
}