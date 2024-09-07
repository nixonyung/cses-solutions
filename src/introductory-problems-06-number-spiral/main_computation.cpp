#include "utils.hpp"

int main() {
    enable_fast_io();

    auto num_tests = read<uint>();
    while (num_tests--) {
        auto y = read<uint>() - 1; // 0-indexed
        auto x = read<uint>() - 1; // 0-indexed

        auto layer_idx = std::max(x, y);
        if (layer_idx & 1) {
            // find the smallest element at layer_idx (the bottom-left element) then move to (x,y)
            std::cout << (ulong)layer_idx * layer_idx + 1 + y + layer_idx - x << '\n';
        } else {
            // find the smallest element at layer_idx (the top-right element) then move to (x,y)
            std::cout << (ulong)layer_idx * layer_idx + 1 + x + layer_idx - y << '\n';
        }
    }
}