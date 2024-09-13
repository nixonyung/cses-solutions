#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto target = read<uint>();
    auto coins = std::vector<uint>(n);
    {
        for (auto &coin : coins) {
            coin = read<uint>();
        }
    }

    auto min_num_coins = std::vector<uint>(target + 1, std::numeric_limits<uint>::max());
    {
        min_num_coins[0] = 0; // initial condition

        for (auto curr_target : iota(1U, target + 1)) {
            for (auto const &coin : coins) {
                if (coin <= curr_target && min_num_coins[curr_target - coin] != std::numeric_limits<uint>::max()) {
                    min_num_coins[curr_target] = std::min(min_num_coins[curr_target], 1 + min_num_coins[curr_target - coin]);
                }
            }
        }
    }
    std::cout << ((min_num_coins[target] < std::numeric_limits<uint>::max()) ? (int)min_num_coins[target]
                                                                             : -1)
              << '\n';
}