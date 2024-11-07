// (ref.) [Eight queens puzzle - Constructing and counting solutions when n = 8](https://wikiwand.com/en/articles/Eight_queens_puzzle#Constructing_and_counting_solutions_when_n_=_8)

#include <algorithm>
#include <iostream>
#include <vector>

namespace {
const unsigned BOARD_SIZE = 8;
const unsigned NUM_CELLS = BOARD_SIZE * BOARD_SIZE;
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto board = std::vector<char>(NUM_CELLS);
    {
        for (unsigned i = 0; i < NUM_CELLS; i++) {
            std::cin >> board[i];
        }
    }

    unsigned num_configurations = 0;
    {
        auto queen_cols = std::vector<unsigned>{0, 1, 2, 3, 4, 5, 6, 7};
        auto slash_occupieds = std::vector<bool>(BOARD_SIZE * 2 - 1, false);
        auto backslash_occupieds = std::vector<bool>(BOARD_SIZE * 2 - 1, false);
        do {
            slash_occupieds.assign(slash_occupieds.size(), false);
            backslash_occupieds.assign(backslash_occupieds.size(), false);

            bool is_valid = true;
            {
                for (unsigned row = 0; row < BOARD_SIZE; row++) {
                    if (
                        (board[row * BOARD_SIZE + queen_cols[row]] == '*')
                        || (slash_occupieds[row + queen_cols[row]])
                        || (backslash_occupieds[row + (BOARD_SIZE - 1 - queen_cols[row])])
                    ) {
                        is_valid = false;
                        break;
                    }
                    slash_occupieds[row + queen_cols[row]] = true;
                    backslash_occupieds[row + (BOARD_SIZE - 1 - queen_cols[row])] = true;
                }
            }
            if (is_valid) num_configurations++;
        } while (std::ranges::next_permutation(queen_cols).found);
    }
    std::cout << num_configurations << '\n';
}
