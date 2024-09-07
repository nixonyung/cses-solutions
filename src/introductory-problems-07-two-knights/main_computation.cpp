#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    // (ref.) [CSES Solutions - Two Knights](https://www.geeksforgeeks.org/cses-solutions-two-knights/)

    for (auto k : iota(1U, n + 1)) {
        // choose 2 cells from the board, order doesn't matter
        auto num_total = (ulong)(k * k) * ((k * k) - 1) / 2;
        // 2 invalid configurations for each 2x3 and 3x2 cells
        auto num_invalid = (ulong)((k - 1) * (k - 2) * 2) * 2;

        std::cout << (num_total - num_invalid) << '\n';
    }
}