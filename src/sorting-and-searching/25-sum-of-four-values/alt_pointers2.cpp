// correct implementation but outputs are different from tests

#include <algorithm>
#include <iostream>
#include <vector>

namespace {
const unsigned K = 4;
}

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
        unsigned sum_lower_bound = 0;
        unsigned sum_upper_bound = 0;
        for (unsigned i = 0; i < K; i++) {
            sum_lower_bound += numbers[i].val;
            sum_upper_bound += numbers[N - 1 - i].val;
        }
        if (sum_lower_bound > TARGET || sum_upper_bound < TARGET) {
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    {
        auto find_k_sum = [&numbers](
                              unsigned k,
                              unsigned target,
                              unsigned numbers_len
                          ) {
            auto impl = [&numbers](
                            auto impl_ref,
                            unsigned k,
                            unsigned target,
                            unsigned numbers_len
                        ) {
                if (k == 2) {
                    unsigned l = 0;
                    unsigned r = numbers_len - 1;
                    while (l < r) {
                        auto const sum = numbers[l].val + numbers[r].val;
                        if (sum == target) {
                            std::cout << numbers[l].id + 1 << ' ' << numbers[r].id + 1;
                            return true;
                        }
                        if (sum < target) l++;
                        else r--;
                    }
                    return false;
                }
                for (unsigned pivot_idx = numbers_len - 1; pivot_idx >= k - 1; pivot_idx--) {
                    {
                        unsigned min_sum = numbers[0].val;
                        unsigned max_sum = numbers[pivot_idx].val;
                        for (unsigned i = 1; i < k; i++) {
                            min_sum += numbers[i].val;
                            max_sum += numbers[pivot_idx - i].val;
                        }
                        if (min_sum > target || max_sum < target) continue;
                    }
                    if (impl_ref(impl_ref, k - 1, target - numbers[pivot_idx].val, pivot_idx)) {
                        std::cout << ' ' << numbers[pivot_idx].id + 1;
                        return true;
                    }
                }
                return false;
            };
            return impl(impl, k, target, numbers_len);
        };
        if (find_k_sum(K, TARGET, (unsigned)numbers.size())) {
            std::cout << '\n';
            return 0;
        }
    }
    std::cout << "IMPOSSIBLE\n";
}