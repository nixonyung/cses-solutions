#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

int main() {
    auto const BOARD_SIZE = 8;

    auto board = std::vector<char>(BOARD_SIZE * BOARD_SIZE);
    for (auto &ch : board) {
        std::cin >> ch;
    }

    // solve by brute force
    // (ref.) [Eight queens puzzle - Constructing and counting solutions when n = 8](https://omni.wikiwand.com/en/articles/Eight_queens_puzzle#Constructing_and_counting_solutions_when_n_=_8)
    auto ans = 0;
    auto queen_cols = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7};
    do {
        /*
        slash_occupied[0] is true iff has_queen[0][0]
        slash_occupied[1] is true iff has_queen[0][1] and has_queen[1][0]
        slash_occupied[2] is true iff has_queen[0][2] and has_queen[1][1] and has_queen[2][0]
        ...
        */
        auto slash_occupied = std::bitset<BOARD_SIZE * 2 - 1>();
        /*
        backslash_occupied[0] is true iff has_queen[0][7]
        backslash_occupied[1] is true iff has_queen[0][6] and has_queen[1][7]
        backslash_occupied[2] is true iff has_queen[0][5] and has_queen[1][6] and has_queen[2][7]
        ...
        */
        auto backslash_occupied = std::bitset<BOARD_SIZE * 2 - 1>();

        auto ok = true;
        for (auto row = 0; row < BOARD_SIZE; row++) {
            if (
                (board[BOARD_SIZE * row + queen_cols[row]] == '*')
                || (slash_occupied[row + queen_cols[row]])
                || (backslash_occupied[row + (BOARD_SIZE - 1 - queen_cols[row])])
            ) {
                ok = false;
                break;
            }
            slash_occupied.set(row + queen_cols[row]);
            backslash_occupied.set(row + (BOARD_SIZE - 1 - queen_cols[row]));
        }
        if (ok) {
            ans++;
        }
    } while (std::ranges::next_permutation(queen_cols).found);
    std::cout << ans << '\n';
}
