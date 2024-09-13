#include "utils.hpp"

int main() {
    const ulong MOD = 1e9 + 7;

    enable_fast_io();

    auto n = read<uint>();
    auto m = read<uint>();

    auto num_wayss = std::vector<ulong>(m + 2, 0);
    auto window = std::vector<ulong>(3); // preallocate memory for the window for num_wayss
    {
        // initial state
        {
            auto input = read<uint>();
            for (auto i : iota(1U, m + 1)) {
                if (input == i || input == 0) {
                    num_wayss[i] = 1;
                }
            }
        }

        // recurrence
        for (auto _ : iota(0U, n - 1)) {
            auto input = read<uint>();
            {
                window[0] = num_wayss[0];
                window[1] = num_wayss[1];
                window[2] = 0;
            }
            for (auto i : iota(1U, m + 1)) {
                window[(i + 1) % 3] = num_wayss[i + 1];
                num_wayss[i] = (input == i || input == 0) ? ((window[0] + window[1] + window[2]) % MOD)
                                                          : 0;
            }
        }
    }
    {
        ulong total_num_ways = 0;
        for (auto const &num_ways : num_wayss) {
            total_num_ways += num_ways;
        }
        std::cout << total_num_ways % MOD << '\n';
    }
}