#include "utils.hpp"

int main() {
    const ulong MOD = 1e9 + 7;

    enable_fast_io();

    auto n = read<uint>();

    {
        auto prev_num_ways = std::vector<ulong>{
            1,                      // 1
            1 + 1,                  // mem[1] + 1
            2 + 1 + 1,              // mem[2] + mem[1] + 1
            4 + 2 + 1 + 1,          // mem[3] + mem[2] + mem[1] + 1
            8 + 4 + 2 + 1 + 1,      // mem[4] + mem[3] + mem[2] + mem[1] + 1
            16 + 8 + 4 + 2 + 1 + 1, // mem[5] + mem[4] + mem[3] + mem[2] + mem[1] + 1
        };
        switch (n) {
        case 1:
            std::cout << prev_num_ways[0] << '\n';
            break;
        case 2:
            std::cout << prev_num_ways[1] << '\n';
            break;
        case 3:
            std::cout << prev_num_ways[2] << '\n';
            break;
        case 4:
            std::cout << prev_num_ways[3] << '\n';
            break;
        case 5:
            std::cout << prev_num_ways[4] << '\n';
            break;
        case 6:
            std::cout << prev_num_ways[5] << '\n';
            break;
        default:
            ulong curr_num_ways = prev_num_ways[0] + prev_num_ways[1] + prev_num_ways[2] + prev_num_ways[3] + prev_num_ways[4] + prev_num_ways[5];
            for (auto _ : iota(8U, n + 1)) {
                std::ranges::rotate(prev_num_ways, prev_num_ways.begin() + 1);
                prev_num_ways.back() = curr_num_ways;
                curr_num_ways = (prev_num_ways[0] + prev_num_ways[1] + prev_num_ways[2] + prev_num_ways[3] + prev_num_ways[4] + prev_num_ways[5]) % MOD;
            }
            std::cout << curr_num_ways << '\n';
            break;
        }
    }
}