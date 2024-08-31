#define VERSION_BINARY_SEARCH 1
#define VERSION_POINTERS 2

#define VERSION VERSION_POINTERS

#include "../../lib/cses_io.hpp"
#include <algorithm>

int main() {
    cses::enable_fast_io();

    auto [n, x] = cses::read_tuple<int, int>();
    if (n == 1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    auto inputs = cses::read_vector_with_ids<int>(n);

    // using `stable_sort` just to make the output matches with the test output,
    // using `sort` is also correct and should be faster
    std::ranges::stable_sort(
        inputs,
        [](auto const &lhs, auto const &rhs) {
            return lhs.val < rhs.val;
        }
    );

    /*
    analyzing VERSION_BINARY_SEARCH:
        Time complexity = O(log(n) + log(n-1) + ... + log(1))  (because of running binary search on array with decreasing size)
                        = O(nlogn)

        Should be faster when there are a lot of elements to skip at each increment of `left`,
        e.g.
            x = 100
            a[] = [1, 11, 50, 50, ...(hundreds of 90), ...(hundreds of 100)]
                          ^   ^

    analyzing VERSION_POINTERS:
        Time complexity = O(n) because left and right together will at most traverse all `a` once.
        It is also more cache-friendly.

        Should be faster when there are only a few elements to skip at each increment of `left`,
        e.g.
            x = 100
            a[] = [...(hundreds of 1), ...(hundreds of 11), 50, 50, 90, 100]
                                                            ^   ^
    */
#if VERSION == VERSION_BINARY_SEARCH
    for (auto left = 0; left < n - 1; left++) {
        // using `upper_bound` just to make the output matches with the test output,
        // using `lower_bound` should also work
        auto right = int(
            std::upper_bound(
                inputs.begin() + left,
                inputs.begin() + n,
                x - inputs[left].val,
                [](const auto &val, const auto &input) {
                    return val < input.val;
                }
            )
            - inputs.begin()
        );
        /*
        pointers are not valid if either:
            - left == right-1 (because the resulting indices have to be distinct)
            - left > right-1 (logically wrong)
        */
        if (left < right - 1 && inputs[left].val + inputs[right - 1].val == x) {
            std::cout << inputs[left].id + 1
                      << ' '
                      << inputs[right - 1].id + 1
                      << '\n';
            return 0;
        }
    }
    std::cout << "IMPOSSIBLE\n";
#elif VERSION == VERSION_POINTERS
    // right is the smallest index s.t. a[left] + a[right] > x
    auto right = n;
    for (auto left = 0; left < right - 1; left++) {
        if (inputs[left].val + inputs[right - 1].val == x) {
            std::cout << inputs[left].id + 1
                      << ' '
                      << inputs[right - 1].id + 1
                      << '\n';
            return 0;
        }

        // decrement `right` while maintaining a[left] + a[right] > x
        while (left < right - 1 && inputs[left].val + inputs[right - 1].val > x) {
            right--;
        }
        if (left < right - 1 && inputs[left].val + inputs[right - 1].val == x) {
            std::cout << inputs[left].id + 1
                      << ' '
                      << inputs[right - 1].id + 1
                      << '\n';
            return 0;
        }
    }
    std::cout << "IMPOSSIBLE\n";
#endif
}
