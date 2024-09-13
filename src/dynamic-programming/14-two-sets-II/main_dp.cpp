#include "utils.hpp"

int main() {
    const ulong MOD = 1e9 + 7;

    enable_fast_io();

    auto n = read<uint>();
    // refer to introductory-problems/08-two-sets solution
    if (!((n - 1) & 2)) {
        std::cout << 0 << '\n';
        std::exit(0);
    }

    auto sum_numbers = n * (n + 1) / 2;
    auto num_wayss = std::vector<ulong>(sum_numbers + 1, 0);
    {
        // terminal state
        num_wayss[0] = 1;

        // recurrence
        for (auto number : iota(1U, n + 1)) { // loop actions then loop states -> find combinations
            for (
                auto i : iota(number, sum_numbers + 1) |
                             std::views::reverse // reverse -> "0-1 knapsack"
            ) {
                num_wayss[i] = (num_wayss[i] + num_wayss[i - number]) %
                               (MOD * 2); // note: x / 2 % MOD = x % (2*MOD) / 2
            }
        }
    }
    std::cout << num_wayss[sum_numbers / 2] / 2 // eliminate double counting
              << '\n';
}