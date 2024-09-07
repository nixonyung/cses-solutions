#include "utils.hpp"

int main() {
    enable_fast_io();

    /*
    implementations that won't work:
        - store a flag for all x to indicate if it has appeared
            => x <= 1e9 is too large
    */

    auto n = read<uint>();

    auto inputs = std::vector<uint>(n);
    {
        for (auto &input : inputs) {
            input = read<uint>();
        }
        radix_sort(inputs);
    }

    uint num_unique = 1;
    {
        for (auto i : iota(1U, n)) {
            if (inputs[i] != inputs[i - 1]) {
                num_unique++;
            }
        }
    }
    std::cout << num_unique << '\n';
}