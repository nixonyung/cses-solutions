#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<ulong>();

    std::cout << n << ' ';
    while (n != 1) {
        n = (n & 1) ? (n * 3 + 1) : (n >> 1);
        std::cout << n << ' ';
    }
    std::cout << '\n';
}