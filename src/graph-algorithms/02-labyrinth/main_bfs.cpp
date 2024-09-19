#include <iostream>
#include <queue>
#include <ranges>

using std::views::iota;

namespace {
enum class VisitedFrom {
    UNKNOWN,
    NIL, // used for start_cell
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

struct Cell {
    uint row;
    uint col;
    uint path_len;
    VisitedFrom from = VisitedFrom::UNKNOWN;
};
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint height;
    uint width;
    {
        std::cin >> height >> width;
    }

    auto board = std::vector<char>(height * width);
    Cell start_cell;
    {
        for (auto const &row : iota(0U, height)) {
            for (auto const &col : iota(0U, width)) {
                std::cin >> board[row * width + col];
                if (board[row * width + col] == 'A') {
                    start_cell = {row, col, 0, VisitedFrom::NIL};
                }
            }
        }
    }

    {
        auto visited_froms = std::vector<VisitedFrom>(height * width, VisitedFrom::UNKNOWN);
        auto to_visits = std::queue<Cell>();
        auto can_visit = [&width, &board, &visited_froms](int row, int col) {
            return board[row * width + col] != '#' && visited_froms[row * width + col] == VisitedFrom::UNKNOWN;
        };

        to_visits.push(start_cell);
        while (!to_visits.empty()) {
            auto const [row, col, path_len, from] = to_visits.front();
            to_visits.pop();

            if (visited_froms[row * width + col] != VisitedFrom::UNKNOWN) {
                continue;
            }
            visited_froms[row * width + col] = from;

            if (board[row * width + col] == 'B') {
                std::cout << "YES" << '\n'
                          << path_len << '\n';

                auto path = std::vector<char>(path_len);
                {
                    uint curr_row = row;
                    uint curr_col = col;
                    uint i = path_len - 1;
                    while (curr_row != start_cell.row || curr_col != start_cell.col) {
                        switch (visited_froms[curr_row * width + curr_col]) {
                        case VisitedFrom::UP: {
                            path[i--] = 'D';
                            curr_row--;
                        } break;
                        case VisitedFrom::DOWN: {
                            path[i--] = 'U';
                            curr_row++;
                        } break;
                        case VisitedFrom::LEFT: {
                            path[i--] = 'R';
                            curr_col--;
                        } break;
                        case VisitedFrom::RIGHT: {
                            path[i--] = 'L';
                            curr_col++;
                        } break;
                        default: {
                        } break;
                        }
                    }
                }
                for (auto const &ch : path) {
                    std::cout << ch;
                }
                std::cout << '\n';
                std::exit(0);
            }

            if (col < width - 1 && can_visit(row, col + 1)) {
                to_visits.push({row, col + 1, path_len + 1, VisitedFrom::LEFT});
            }
            if (col > 0 && can_visit(row, col - 1)) {
                to_visits.push({row, col - 1, path_len + 1, VisitedFrom::RIGHT});
            }
            if (row < height - 1 && can_visit(row + 1, col)) {
                to_visits.push({row + 1, col, path_len + 1, VisitedFrom::UP});
            }
            if (row > 0 && can_visit(row - 1, col)) {
                to_visits.push({row - 1, col, path_len + 1, VisitedFrom::DOWN});
            }
        }
    }
    std::cout << "NO\n";
}