#include "utils.hpp"

namespace {
struct Input {
    uint id;
    uint val;
};
} // namespace

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto target = read<uint>();
    if (n < 4) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    auto inputs = std::vector<Input>(n);
    {
        for (uint i = 0; auto &input : inputs) {
            input = {(i++) + 1, read<uint>()};
        }
        radix_sort(
            inputs,
            [](auto const &input) { return input.val; }
        );
        if (
            inputs[0].val + inputs[1].val + inputs[2].val + inputs[3].val > target ||
            inputs[n - 4].val + inputs[n - 3].val + inputs[n - 2].val + inputs[n - 1].val < target
        ) {
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    for (auto fixed1 : iota(0U, n - 3)) {
        if (inputs[fixed1].val + inputs[fixed1 + 1].val + inputs[fixed1 + 2].val + inputs[fixed1 + 3].val > target ||
            inputs[fixed1].val + inputs[n - 3].val + inputs[n - 2].val + inputs[n - 1].val < target) {
            continue;
        }
        for (auto fixed2 : iota(fixed1 + 1, n - 2)) {
            if (inputs[fixed1].val + inputs[fixed2].val + inputs[fixed2 + 1].val + inputs[fixed2 + 2].val > target ||
                inputs[fixed1].val + inputs[fixed2].val + inputs[n - 2].val + inputs[n - 1].val < target) {
                continue;
            }

            uint left = fixed2 + 1;
            uint right = n - 1;
            while (left < right) {
                auto sum = inputs[fixed1].val + inputs[fixed2].val + inputs[left].val + inputs[right].val;
                if (sum == target) {
                    std::cout << inputs[fixed1].id << ' ' << inputs[fixed2].id << ' ' << inputs[left].id << ' ' << inputs[right].id << '\n';
                    return 0;
                } else if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
    }
    std::cout << "IMPOSSIBLE\n";
}