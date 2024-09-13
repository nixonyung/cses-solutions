#include "utils.hpp"

namespace {
// (ref.) [Recursive solution](https://omni.wikiwand.com/en/articles/Tower_of_Hanoi#Recursive_solution)
auto move_disks(uint n, uint source, uint spare, uint target) {
    if (n == 1) {
        std::cout << source << ' ' << target << '\n';
        return;
    }

    move_disks(n - 1, source, target, spare);
    std::cout << source << ' ' << target << '\n';
    move_disks(n - 1, spare, source, target);
}
} // namespace

int main() {
    enable_fast_io();

    auto n = read<uint>();

    /*
    consider the recursive solution, observe that:
        hanoi(1) = 1
        hanoi(2) = 1+2*hanoi(1) = 1+2     = 3
        hanoi(3) = 1+2*hanoi(2) = 1+2+4   = 7
        hanoi(4) = 1+2*hanoi(3) = 1+2+4+8 = 15
        ...
    we have hanoi(n) = 1+2*hanoi(n-1)+1 = sum_{k=1}^{n-1} 2^k = 2^n - 1
    */
    auto num_moves = (1U << n) - 1;

    std::cout << num_moves << '\n';
    move_disks(n, 1, 2, 3);
}
