#include "utils.hpp"

int main() {
    const ulong MOD = 1e9 + 7;

    enable_fast_io();

    auto n = read<uint>();
    auto board = std::vector<char>(n * n);
    {
        for (auto &cell : board) {
            cell = read<char>();
        }
    }

    auto num_pathss = std::vector<ulong>(n, 0); // only store the prev row
    {
        // boundary condition
        num_pathss[n - 1] = 1; // num_pathss[n-1][n-1] = 1

        for (auto row : iota(0U, n) | std::views::reverse) {
            if (board[row * n + n - 1] == '*') {
                num_pathss[n - 1] = 0;
            }
            for (auto col : iota(0U, n - 1) | std::views::reverse) {
                if (board[row * n + col] == '*') {
                    num_pathss[col] = 0;
                } else {
                    num_pathss[col] = (num_pathss[col] + num_pathss[col + 1]) % MOD;
                }
            }
        }
    }
    std::cout << num_pathss[0] << '\n';
}