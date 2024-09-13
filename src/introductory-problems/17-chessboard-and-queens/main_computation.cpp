#include "utils.hpp"
#include <bitset>

int main() {
    const uint BOARD_SIZE = 8;

    enable_fast_io();

    auto board = std::vector<char>(BOARD_SIZE * BOARD_SIZE);
    for (auto &ch : board) {
        ch = read<char>();
    }

    // solve by brute force
    // (ref.) [Eight queens puzzle - Constructing and counting solutions when n = 8](https://omni.wikiwand.com/en/articles/Eight_queens_puzzle#Constructing_and_counting_solutions_when_n_=_8)
    auto num_valid = 0;
    {
        auto queen_cols = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7};
        auto slash_occupied = std::bitset<BOARD_SIZE * 2 - 1>();
        auto backslash_occupied = std::bitset<BOARD_SIZE * 2 - 1>();
        do {
            slash_occupied.reset();
            backslash_occupied.reset();

            bool ok = true;
            for (auto row : iota(0U, BOARD_SIZE)) {
                if (
                    (board[BOARD_SIZE * row + queen_cols[row]] == '*') ||
                    (slash_occupied[row + queen_cols[row]]) ||
                    (backslash_occupied[row + (BOARD_SIZE - 1 - queen_cols[row])])
                ) {
                    ok = false;
                    break;
                }
                slash_occupied.set(row + queen_cols[row]);
                backslash_occupied.set(row + (BOARD_SIZE - 1 - queen_cols[row]));
            }
            if (ok) {
                num_valid++;
            }
        } while (std::ranges::next_permutation(queen_cols).found);
    }
    std::cout << num_valid << '\n';
}
