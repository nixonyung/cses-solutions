#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned TARGET;
    {
        std::cin >> N >> TARGET;
    }
    if (N == 1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    struct Number {
        unsigned id;
        unsigned val;
    };
    auto numbers = std::vector<Number>(N);
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> numbers[i].val;
            numbers[i].id = i;
        }
        std::ranges::stable_sort(
            numbers,
            {},
            [](Number const &number) { return number.val; }
        );
    }

    /*
    `r` is the smallest index satisfying `vals[l] + vals[r] > x` (to match with test outputs).

    find `r` using binary search:
        Time complexity = O(log(n) + log(n-1) + ... + log(1))  (because of running binary search on array with decreasing size)
                        = O(nlogn)

        Faster for cases where there are a lot of elements to skip at each increment of `l`, e.g.
            x = 100
            a[] = [1, 11, 50, 50, ...(hundreds of 90), ...(hundreds of 100)]
    */
    for (unsigned l = 0; l < N - 1; l++) {
        unsigned r = (unsigned)std::distance(
            numbers.begin(),
            std::ranges::upper_bound(
                numbers | std::views::drop(l + 1),
                TARGET - numbers[l].val,
                {},
                [](Number const &number) { return number.val; }
            ) - 1
        );
        if (l < r && numbers[l].val + numbers[r].val == TARGET) {
            std::cout << numbers[l].id + 1 << ' ' << numbers[r].id + 1 << '\n';
            return 0;
        }
    }
    std::cout << "IMPOSSIBLE\n";
}
