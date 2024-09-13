#include "utils.hpp"

namespace {
struct Input {
    uint id;
    uint val;
};

inline auto get_sum(
    uint pos1,
    uint pos2,
    uint pos3,
    std::vector<Input> const &inputs
) {
    return (ulong)inputs[pos1].val + inputs[pos2].val + inputs[pos3].val;
}
} // namespace

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto target = read<uint>();
    if (n < 3) {
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
            get_sum(0, 1, 2, inputs) > target ||
            get_sum(n - 3, n - 2, n - 1, inputs) < target
        ) {
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    // (ref.) [CSES - Sum of Three Values](https://usaco.guide/problems/cses-1641-sum-of-three-values/solution)

    for (auto fixed : iota(0U, n - 2)) {
        if (get_sum(fixed, n - 2, n - 1, inputs) < target) {
            continue;
        }

        uint left = fixed + 1;
        uint right = n - 1;
        while (left < right) {
            auto const &sum = get_sum(fixed, left, right, inputs);
            if (sum == target) {
                std::cout << inputs[fixed].id << ' ' << inputs[left].id << ' ' << inputs[right].id << '\n';
                return 0;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }
    std::cout << "IMPOSSIBLE\n";
}