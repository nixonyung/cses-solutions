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
    /*
    `right` is the smallest index satisfying `vals[left] + vals[right] > x`.

    find `right` by maintaining pointers:
        Time complexity = O(n) because left and right together will at most traverse all `a` once.
        It is also more cache-friendly.

        Faster for cases where there are only a few elements to skip at each increment of `left`,
        e.g.
            x = 100
            a[] = [...(hundreds of 1), ...(hundreds of 11), 50, 50, 90, 100]
                                                            ^   ^
    */

    int left = 0;
    int right = n;
    while (left < right - 1) {
        // decrement `right` while keeping `vals[left] + vals[right] > x`
        while (left < right - 1 && inputs[left].val + inputs[right - 1].val > target) {
            right--;
        }
        if (left < right - 1 && inputs[left].val + inputs[right - 1].val == target) {
            std::cout << inputs[left].id << ' ' << inputs[right - 1].id << '\n';
            return 0;
        }
        left++;
    }
    std::cout << "IMPOSSIBLE\n";
}
