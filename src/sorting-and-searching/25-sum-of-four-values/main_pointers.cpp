// correct implementation but outputs are different from tests

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
    if (N < 4) {
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

    {
        auto get_sum = [&numbers](
                           unsigned number_idx1,
                           unsigned number_idx2,
                           unsigned number_idx3,
                           unsigned number_idx4
                       ) {
            return (unsigned long)numbers[number_idx1].val +
                   numbers[number_idx2].val +
                   numbers[number_idx3].val +
                   numbers[number_idx4].val;
        };
        if (
            get_sum(0, 1, 2, 3) > TARGET ||
            get_sum(N - 4, N - 3, N - 2, N - 1) < TARGET
        ) {
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }
        for (unsigned pivot1 = 0; pivot1 < N - 3; pivot1++) {
            if (
                get_sum(pivot1, pivot1 + 1, pivot1 + 2, pivot1 + 3) > TARGET ||
                get_sum(pivot1, N - 3, N - 2, N - 1) < TARGET
            ) continue;
            for (unsigned pivot2 = pivot1 + 1; pivot2 < N - 2; pivot2++) {
                if (
                    get_sum(pivot1, pivot2, pivot2 + 1, pivot2 + 2) > TARGET ||
                    get_sum(pivot1, pivot2, N - 2, N - 1) < TARGET
                ) continue;

                unsigned l = pivot2 + 1;
                unsigned r = N - 1;
                while (l < r) {
                    auto const sum = get_sum(pivot1, pivot2, l, r);
                    if (sum == TARGET) {
                        std::cout << numbers[pivot1].id + 1 << ' '
                                  << numbers[pivot2].id + 1 << ' '
                                  << numbers[l].id + 1 << ' '
                                  << numbers[r].id + 1 << '\n';
                        return 0;
                    }
                    if (sum < TARGET) l++;
                    else r--;
                }
            }
        }
    }
    std::cout << "IMPOSSIBLE\n";
}