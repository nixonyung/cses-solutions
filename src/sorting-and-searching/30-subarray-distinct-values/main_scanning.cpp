#include "utils.hpp"
#include <map>

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto target = read<uint>();

    // (ref.) [CSES Solutions - Subarray Distinct Values](https://www.geeksforgeeks.org/cses-solutions-subarray-distinct-values/)

    ulong num_subarrays = 0;
    {
        auto inputs = std::vector<uint>(n);
        auto value_counter = std::map<uint, uint>();
        uint num_unique = 0;
        uint subarray_start = 0;
        for (auto i : iota(0U, n)) {
            inputs[i] = read<uint>();
            num_unique += (value_counter[inputs[i]]++) == 0;
            while (num_unique > target) {
                num_unique -= (--value_counter[inputs[subarray_start++]]) == 0;
            }
            num_subarrays += (i++) - subarray_start + 1; // any arrays in inputs[subarray_start : (i+1)] will satisfy having AT MOST k distinct values,
                                                         // here only count suffix arrays to avoid double counting
        }
    }
    std::cout << num_subarrays << '\n';
}