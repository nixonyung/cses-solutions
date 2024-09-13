#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto target = read<uint>();

    uint num_subarrays = 0;
    {
        auto inputs = std::vector<uint>(n);
        ulong curr_sum = 0;
        uint subarray_start = 0;
        for (auto i : iota(0U, n)) {
            inputs[i] = read<uint>();

            curr_sum += inputs[i];
            while (curr_sum > target) {
                curr_sum -= inputs[subarray_start++];
            }
            if (curr_sum == target) {
                num_subarrays++;
            }
        }
    }
    std::cout << num_subarrays << '\n';
}