#include <iostream>
#include <vector>

namespace {
const unsigned long MOD = 1e9 + 7;
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned BOARD_SIZE;
    {
        std::cin >> BOARD_SIZE;
    }
    auto board = std::vector<char>(BOARD_SIZE * BOARD_SIZE);
    {
        for (unsigned i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
            std::cin >> board[i];
        }
    }
    if (board[BOARD_SIZE * BOARD_SIZE - 1] == '*') {
        std::cout << 0 << '\n';
        return 0;
    }

    auto num_pathss = std::vector<unsigned long>(BOARD_SIZE, 0); // only store the prev row
    {
        for (unsigned row = BOARD_SIZE - 1; row < BOARD_SIZE; row--) {
            for (unsigned col = BOARD_SIZE - 1; col < BOARD_SIZE; col--) {
                num_pathss[col] = (row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1)
                                      // initial condition
                                      ? 1
                                      : (board[row * BOARD_SIZE + col] == '*')
                                            ? 0
                                        : (col == BOARD_SIZE - 1)
                                            ? num_pathss[col]
                                            : (num_pathss[col] + num_pathss[col + 1]) % MOD;
            }
        }
    }
    std::cout << num_pathss[0] << '\n';
}