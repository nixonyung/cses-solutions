#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    auto num_moves = (1U << n) - 1;
    std::cout << num_moves << '\n';

    // (ref.) [Binary solution](https://omni.wikiwand.com/en/articles/Tower_of_Hanoi#Binary_solution)
    auto is_odd = bool(n & 1);
    for (auto i : iota(1U, num_moves + 1)) {
        auto source = (i - (i & -i)) % 3;
        auto target = (i + (i & -i)) % 3;
        if (is_odd) {
            std::cout << source + 1
                      << ' '
                      << target + 1
                      << '\n';
        } else {
            std::cout << ((source == 0) ? 1 : (4 - source))
                      << ' '
                      << ((target == 0) ? 1 : (4 - target))
                      << '\n';
        }
    }
}