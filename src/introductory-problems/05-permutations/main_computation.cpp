#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    // hard-coded solutions for n <= 3
    if (n == 1) {
        std::cout << "1\n";
        return 0;
    }
    if (n == 2 || n == 3) {
        std::cout << "NO SOLUTION\n";
        return 0;
    }

    // solution: enumerate even numbers increasingly, then enumerate odd numbers increasingly
    for (uint i = 2; i <= n; i += 2) {
        std::cout << i << ' ';
    }
    for (uint i = 1; i <= n; i += 2) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}