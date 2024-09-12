#include "utils.hpp"

int main() {
    const ulong MOD = 1e9 + 7;

    enable_fast_io();

    auto n = read<uint>();
    auto m = read<uint>();

    auto num_wayss = std::vector<ulong>(m + 1);
    {
        auto input = read<uint>();
        if (input != 0) {
            std::ranges::fill(num_wayss, 0);
            num_wayss[input] = 1;
        } else {
            std::ranges::fill(num_wayss, 1);
            num_wayss[0] = 0;
        }
    }
    for (auto _ : iota(1U, n)) {
        auto next_num_wayss = std::vector<ulong>(m + 1, 0);
        {
            auto input = read<uint>();
            if (input != 0) {
                next_num_wayss[input] = num_wayss[input];
                if (input > 1) {
                    next_num_wayss[input] += num_wayss[input - 1];
                }
                if (input < m) {
                    next_num_wayss[input] += num_wayss[input + 1];
                }
                next_num_wayss[input] %= MOD;
            } else {
                next_num_wayss[1] = (num_wayss[1] + num_wayss[2]) % MOD;
                for (auto i : iota(2U, m)) {
                    next_num_wayss[i] = (num_wayss[i - 1] + num_wayss[i] + num_wayss[i + 1]) % MOD;
                }
                next_num_wayss[m] = (num_wayss[m - 1] + num_wayss[m]) % MOD;
            }
        }
        num_wayss = next_num_wayss;
    }
    {
        ulong total_num_ways = 0;
        for (auto const &num_ways : num_wayss) {
            total_num_ways += num_ways;
        }
        std::cout << total_num_ways % MOD << '\n';
    }
}