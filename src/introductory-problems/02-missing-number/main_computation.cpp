#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    int xorsum = 0;
    for (auto i : iota(1U, n + 1)) {
        xorsum ^= i;
    }
    for (auto _ : iota(0U, n - 1)) {
        xorsum ^= read<uint>();
    }
    std::cout << xorsum << '\n';
}