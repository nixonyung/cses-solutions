#include "utils.hpp"
#include <map>

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto target = read<uint>();

    // (ref.) [CSES - Subarray Sums II](https://usaco.guide/problems/cses-1661-subarray-sums-ii/solution)

    ulong num_subarrays = 0;
    {
        auto inputs = std::vector<int>(n);
        long curr_sum = 0;
        auto prefix_sum_counter = std::map<long, uint>{
            {0, 1}  // initial condition
        };
        for (auto i : iota(0U, n)) {
            inputs[i] = read<int>();

            curr_sum += inputs[i];
            num_subarrays += prefix_sum_counter[curr_sum - target]; // want curr_sum - prefix_sum = target
            prefix_sum_counter[curr_sum]++;
        }
    }
    std::cout << num_subarrays << '\n';
}