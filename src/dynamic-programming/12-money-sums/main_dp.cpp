#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    auto coins = std::vector<uint>(n);
    uint sum_coins = 0;
    {
        for (auto &coin : coins) {
            coin = read<uint>();
            sum_coins += coin;
        }
    }

    auto is_possible = std::vector<uint>(sum_coins + 1, false);
    uint num_is_possible = 0;
    {
        // terminal state
        is_possible[0] = true;

        // recurrence
        for (auto const &coin : coins) {
            for (
                auto curr_sum : iota(coin, sum_coins + 1) |
                                    std::views::reverse // update in reverse order so that is_possible[curr_sum - coin] will not include the current coin
            ) {
                if (is_possible[curr_sum - coin]) {
                    num_is_possible += !is_possible[curr_sum];
                    is_possible[curr_sum] = true;
                }
            }
        }
    }
    {
        std::cout << num_is_possible << '\n';
        for (auto i : iota(1U, sum_coins + 1)) {
            if (is_possible[i]) {
                std::cout << i << ' ';
            }
        }
        std::cout << '\n';
    }
}