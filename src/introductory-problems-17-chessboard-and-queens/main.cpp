#include <algorithm>
#include <cstdio>

int main() {
    constexpr int BOARD_SIZE = 8;

    char board[BOARD_SIZE][BOARD_SIZE + 1];
    for (int i = 0; i < BOARD_SIZE; i++) {
        scanf("%s", board[i]);
    }

    // solve by brute force
    // (ref.) [Eight queens puzzle - Constructing and counting solutions when n = 8](https://omni.wikiwand.com/en/articles/Eight_queens_puzzle#Constructing_and_counting_solutions_when_n_=_8)
    int ans = 0;
    int queen_cols[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++) {
        queen_cols[i] = i;
    }
    do {
        /*
        slash_occupied[0] is true iff has_queen[0][0]
        slash_occupied[1] is true iff has_queen[0][1] and has_queen[1][0]
        slash_occupied[2] is true iff has_queen[0][2] and has_queen[1][1] and has_queen[2][0]
        ...
        */
        bool slash_occupied[BOARD_SIZE * 2 - 1]; // "/"
        for (int i = 0; i < BOARD_SIZE * 2 - 1; i++) {
            slash_occupied[i] = false;
        }
        /*
        backslash_occupied[0] is true iff has_queen[0][7]
        backslash_occupied[1] is true iff has_queen[0][6] and has_queen[1][7]
        backslash_occupied[2] is true iff has_queen[0][5] and has_queen[1][6] and has_queen[2][7]
        ...
        */
        bool backslash_occupied[BOARD_SIZE * 2 - 1]; // "\"
        for (int i = 0; i < BOARD_SIZE * 2 - 1; i++) {
            backslash_occupied[i] = false;
        }

        bool ok = true;
        for (int row = 0; row < BOARD_SIZE; row++) {
            if (
                (board[row][queen_cols[row]] == '*') ||
                (slash_occupied[row + queen_cols[row]]) ||
                (backslash_occupied[row + (BOARD_SIZE - 1 - queen_cols[row])])) {
                ok = false;
                break;
            }
            slash_occupied[row + queen_cols[row]] = true;
            backslash_occupied[row + (BOARD_SIZE - 1 - queen_cols[row])] = true;
        }
        if (ok) {
            ans++;
        }
    } while (std::next_permutation(queen_cols, queen_cols + BOARD_SIZE));
    printf("%d\n", ans);
}
