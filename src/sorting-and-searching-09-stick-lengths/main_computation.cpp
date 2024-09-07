#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    auto inputs = std::vector<uint>(n);
    for (auto &input : inputs) {
        input = read<uint>();
    }

    // use median as the target length

    radix_sort(inputs);
    auto median = inputs[n >> 1];

    ulong ans = 0;
    for (auto input : inputs | std::views::take(n >> 1)) {
        ans += median - input;
    }
    for (auto input : inputs | std::views::drop(n >> 1)) {
        ans += input - median;
    }
    std::cout << ans << '\n';
}