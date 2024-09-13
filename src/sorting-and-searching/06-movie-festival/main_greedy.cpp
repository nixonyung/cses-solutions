#include "utils.hpp"

namespace {
struct Input {
    uint start; // inclusive
    uint end;   // exclusive
};
} // namespace

int main() {
    enable_fast_io();

    auto n = read<uint>();

    auto inputs = std::vector<Input>(n);
    {
        for (auto &input : inputs) {
            input.start = read<uint>();
            input.end = read<uint>();
        }
    }

    // greedy solution: at each step, try to pick the smallest `b`

    radix_sort(
        inputs,
        [](auto const &input) { return input.end; }
    );

    uint ans = 0;
    {
        uint last_b = 0;
        for (auto const &input : inputs) {
            if (input.start >= last_b) {
                ans++;
                last_b = input.end;
            }
        }
    }
    std::cout << ans << '\n';
}