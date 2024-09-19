#include "utils.hpp"
#include <bitset>
#include <stack>

namespace {
struct Cell {
    uint row;
    uint col;
};
} // namespace

int main() {
    enable_fast_io();

    const uint MAX_HEIGHT = 1000;
    const uint MAX_WIDTH = 1000;

    auto height = read<uint>();
    auto width = read<uint>();
    auto board = std::vector<char>(height * width);
    {
        std::ranges::generate(board, read<char>);
    }

    uint num_rooms = 0;
    {
        auto visiteds = std::bitset<MAX_HEIGHT * MAX_WIDTH>();
        auto to_visits = std::stack<Cell, std::vector<Cell>>();
        auto can_visit = [&width, &board, &visiteds](int row, int col) {
            return board[row * width + col] != '#' && !visiteds[row * width + col];
        };
        for (auto const &row : iota(0U, height)) {
            for (auto const &col : iota(0U, width)) {
                if (can_visit(row, col)) {
                    num_rooms++;

                    to_visits.push({row, col});
                    while (!to_visits.empty()) {
                        auto const [row, col] = to_visits.top();
                        to_visits.pop();

                        if (visiteds[row * width + col]) {
                            continue;
                        }
                        visiteds[row * width + col] = true;

                        if (col > 0 && can_visit(row, col - 1)) {
                            to_visits.push({row, col - 1});
                        }
                        if (col < width - 1 && can_visit(row, col + 1)) {
                            to_visits.push({row, col + 1});
                        }
                        if (row > 0 && can_visit(row - 1, col)) {
                            to_visits.push({row - 1, col});
                        }
                        if (row < height - 1 && can_visit(row + 1, col)) {
                            to_visits.push({row + 1, col});
                        }
                    }
                }
            }
        }
    }
    std::cout << num_rooms << '\n';
}