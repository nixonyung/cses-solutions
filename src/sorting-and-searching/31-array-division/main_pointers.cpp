// (ref.) [CSES - Array Division](https://usaco.guide/problems/cses-1085-array-division/solution)

#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned NUM_SUBARRAYS;
    {
        std::cin >> N >> NUM_SUBARRAYS;
    }
    auto numbers = std::vector<unsigned>(N);
    unsigned long numbers_sum = 0;
    decltype(numbers)::value_type min_number = -1;
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> numbers[i];
            numbers_sum += numbers[i];
            min_number = std::min(min_number, numbers[i]);
        }
    }
    if (NUM_SUBARRAYS == 1) {
        std::cout << numbers_sum << '\n';
        return 0;
    }
    std::cout << *std::ranges::lower_bound(
                     std::views::iota(0UL, numbers_sum),
                     true,
                     {},
                     [&numbers, NUM_SUBARRAYS](auto const &target_max_sum) {
                         unsigned long sum = 0;
                         unsigned num_subarrays = 1;
                         for (auto const &number : numbers) {
                             if (number > target_max_sum) return false;
                             if (sum + number > target_max_sum) {
                                 num_subarrays++;
                                 if (num_subarrays > NUM_SUBARRAYS) return false;
                                 sum = number;
                                 continue;
                             }
                             sum += number;
                         }
                         return true;
                     }
                 )
              << '\n';
}