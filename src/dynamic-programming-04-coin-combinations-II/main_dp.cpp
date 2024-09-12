#include "utils.hpp"

int main() {
    const ulong MOD = 1e9 + 7;

    enable_fast_io();

    auto n = read<uint>();
    auto target = read<uint>();
    auto coins = std::vector<uint>(n);
    {
        for (auto &coin : coins) {
            coin = read<uint>();
        }
    }

    auto num_combinations = std::vector<ulong>(target + 1, 0);
    {
        // boundary condition
        num_combinations[0] = 1;

        for (auto const &coin : coins) {
            for (auto curr_target : iota(0U, target)) {
                if (curr_target + coin <= target) {
                    num_combinations[curr_target + coin] = (num_combinations[curr_target] + num_combinations[curr_target + coin]) % MOD;
                }
            }
        }
    }
    std::cout << num_combinations[target] << '\n';
}