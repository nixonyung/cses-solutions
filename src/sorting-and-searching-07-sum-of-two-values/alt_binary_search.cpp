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
    if (n == 1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    auto target = read<uint>();

    auto inputs = std::vector<Input>(n);
    {
        for (uint i = 0; auto &input : inputs) {
            input = {(i++) + 1, read<uint>()};
        }
        radix_sort(
            inputs,
            [](auto const &input) { return input.val; }
        );
    }

    for (auto left : iota(0U, n - 1)) {
        /*
        `right` is the smallest index satisfying `vals[left] + vals[right] > x`.

        find `right` using binary search:
            Time complexity = O(log(n) + log(n-1) + ... + log(1))  (because of running binary search on array with decreasing size)
                            = O(nlogn)

            Faster for cases where there are a lot of elements to skip at each increment of `left`,
            e.g.
                x = 100
                a[] = [1, 11, 50, 50, ...(hundreds of 90), ...(hundreds of 100)]
        */
        auto right = find_first_valid(
            n,
            [&](auto const &pos) {
                return inputs[left].val + inputs[pos].val > target;
            }
        );
        if (
            left < right - 1 &&
            inputs[left].val + inputs[right - 1].val == target
        ) {
            std::cout << inputs[left].id << ' ' << inputs[right - 1].id << '\n';
            return 0;
        }
    }
    std::cout << "IMPOSSIBLE\n";
}
