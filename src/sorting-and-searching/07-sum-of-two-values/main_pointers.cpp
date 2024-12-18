#include <algorithm>
#include <iostream>
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
    `r` is the smallest index satisfying `vals[left] + vals[r] > x` (to match with test outputs).

    find `r` by maintaining pointers:
        Time complexity = O(n) because `l` and `r` together will at most traverse all `a` once.
        It is also more cache-friendly.

        Faster for cases where there are only a few elements to skip at each increment of `l`, e.g.:
            x = 100
            a[] = [...(hundreds of 1), ...(hundreds of 11), 50, 50, 90, 100]
                                                            ^   ^
    */
    unsigned l = 0;
    unsigned r = N - 1;
    while (r < N && l < r) {
        // decrement `right` while keeping `vals[left] + vals[right] > x`
        while (l < r && numbers[l].val + numbers[r].val > TARGET) r--;
        if (l < r && numbers[l].val + numbers[r].val == TARGET) {
            std::cout << numbers[l].id + 1 << ' ' << numbers[r].id + 1 << '\n';
            return 0;
        }
        l++;
    }
    std::cout << "IMPOSSIBLE\n";
}
