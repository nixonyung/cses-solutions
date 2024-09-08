#include "utils.hpp"

namespace {
struct Input {
    uint id;
    uint val;
};

template <uint K>
bool find_k_sum(
    std::vector<uint> &anss,
    std::vector<Input> const &inputs,
    uint target,
    uint start = 0
) {
    for (auto fixed : iota(start, inputs.size() + 1 - K)) {
        {
            uint min_sum = inputs[fixed].val;
            uint max_sum = inputs[fixed].val;
            for (auto i : iota(1U, K)) {
                min_sum += inputs[fixed + i].val;
                max_sum += inputs[inputs.size() - i].val;
            }
            if (min_sum > target || max_sum < target) {
                continue;
            }
        }
        if (find_k_sum<K - 1>(anss, inputs, target - inputs[fixed].val, fixed + 1)) {
            anss[anss.size() - K] = inputs[fixed].id;
            return true;
        }
    }
    return false;
}

template <>
bool find_k_sum<2>(
    std::vector<uint> &anss,
    std::vector<Input> const &inputs,
    uint target,
    uint start
) {
    uint left = start;
    uint right = (uint)inputs.size() - 1;
    while (left < right) {
        auto sum = inputs[left].val + inputs[right].val;
        if (sum == target) {
            anss[anss.size() - 2] = inputs[left].id;
            anss[anss.size() - 1] = inputs[right].id;
            return true;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    return false;
}
} // namespace

int main() {
    enable_fast_io();

    const uint K = 4;

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

    auto anss = std::vector<uint>(K);
    {
        if (find_k_sum<K>(anss, inputs, target)) {
            for (auto const &ans : anss) {
                std::cout << ans << ' ';
            }
            std::cout << '\n';
        } else {
            std::cout << "IMPOSSIBLE\n";
        }
    }
}