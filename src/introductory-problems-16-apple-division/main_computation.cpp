#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    /*
    solve by enumerating all possible bitmasks:
        for the k-th bit in the bitmask, if the bit == 0, assign pk to group 1, else to group 2
    */

    auto inputs = std::vector<uint>(n);
    for (auto &input : inputs) {
        input = read<uint>();
    }

    ulong min_diff;
    {
        ulong sum1 = 0;
        ulong sum2 = 0;
        for (auto const &p : inputs) {
            sum1 += p;
        }
        min_diff = sum1;

        uint bitmask = 0;
        // using "iterative Gray code" as an optimization
        for (auto i : iota(1U, 1U << n)) {
            auto p_idx = std::countr_zero(i);
            bitmask ^= 1U << p_idx;
            if (bitmask & (1U << p_idx)) {
                sum2 += inputs[p_idx];
                sum1 -= inputs[p_idx];
            } else {
                sum1 += inputs[p_idx];
                sum2 -= inputs[p_idx];
            }
            min_diff = std::min(min_diff, (ulong)std::labs((long)sum1 - (long)sum2));
        }
    }
    std::cout << min_diff << '\n';
}
