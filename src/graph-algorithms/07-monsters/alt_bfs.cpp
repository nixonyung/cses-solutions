#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>

namespace {
struct Cell {
    static inline uint32_t BOARD_WIDTH;

    uint32_t id;
    uint32_t row;
    uint32_t col;

    Cell(uint32_t row, uint32_t col)
        : id(row * BOARD_WIDTH + col),
          row(row),
          col(col) {
    }
};

enum class VisitFrom : uint8_t {
    UNKNOWN,
    NIL, // used for starting cells
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

enum class VisitBy : uint8_t {
    UNKNOWN,
    PLAYER,
    MONSTER,
};

struct State {
    VisitBy visit_by; // `visit_by == UNKNOWN` invalidates other fields
    VisitFrom visit_from;
    uint32_t distance; // the shortest distance from any `visit_by` to this cell
};
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t height;
    uint32_t width;
    {
        std::cin >> height >> width;
        Cell::BOARD_WIDTH = width;
    }

    auto board = std::vector<char>(height * width);
    auto states = std::vector<State>(height * width, {VisitBy::UNKNOWN, VisitFrom::UNKNOWN, 0});
    auto to_explores = std::queue<Cell>();
    {
        Cell start = {0, 0}; // dummy init value
        for (uint32_t row = 0; row < height; row++) {
            for (uint32_t col = 0; col < width; col++) {
                auto cell = Cell{row, col};
                std::cin >> board[cell.id];
                if (board[cell.id] == 'A') {
                    if (
                        row == 0 || row == height - 1 ||
                        col == 0 || col == width - 1
                    ) {
                        std::cout << "YES\n0\n\n";
                        std::exit(0);
                    }
                    start = cell;
                } else if (board[cell.id] == 'M') {
                    states[cell.id] = {VisitBy::MONSTER, VisitFrom::NIL, 0};
                    to_explores.push(cell);
                }
            }
        }
        // explore `start` after exploring monsters
        states[start.id] = {VisitBy::PLAYER, VisitFrom::NIL, 0};
        to_explores.push(start);
    }

    auto adjs = [&](Cell const &cell) {
        auto adjs = std::vector<std::tuple<Cell, VisitFrom>>();
        {
            if (cell.col > 0) {
                adjs.push_back({
                    {cell.row, cell.col - 1},
                    VisitFrom::RIGHT
                });
            }
            if (cell.col < width - 1) {
                adjs.push_back({
                    {cell.row, cell.col + 1},
                    VisitFrom::LEFT
                });
            }
            if (cell.row > 0) {
                adjs.push_back({
                    {cell.row - 1, cell.col},
                    VisitFrom::DOWN
                });
            }
            if (cell.row < height - 1) {
                adjs.push_back({
                    {cell.row + 1, cell.col},
                    VisitFrom::UP
                });
            }
        }
        return adjs;
    };
    while (!to_explores.empty()) {
        auto const cell = to_explores.front();
        auto const &visit_by = states[cell.id].visit_by;
        to_explores.pop();

        for (auto const &[adj, visit_from] : adjs(cell)) {
            if (board[adj.id] == '#' || states[adj.id].visit_by != VisitBy::UNKNOWN) continue;
            states[adj.id] = {visit_by, visit_from, states[cell.id].distance + 1};

            if (
                (adj.row == 0 || adj.row == height - 1 ||
                 adj.col == 0 || adj.col == width - 1) &&
                visit_by == VisitBy::PLAYER
            ) {
                auto path = std::string(states[adj.id].distance, 'x');
                {
                    auto curr_cell = adj;
                    for (int32_t i = (int32_t)path.size() - 1; i >= 0; i--) {
                        switch (states[curr_cell.id].visit_from) {
                        case VisitFrom::UP: {
                            path[i] = 'D';
                            curr_cell = {curr_cell.row - 1, curr_cell.col};
                        } break;
                        case VisitFrom::DOWN: {
                            path[i] = 'U';
                            curr_cell = {curr_cell.row + 1, curr_cell.col};
                        } break;
                        case VisitFrom::LEFT: {
                            path[i] = 'R';
                            curr_cell = {curr_cell.row, curr_cell.col - 1};
                        } break;
                        case VisitFrom::RIGHT: {
                            path[i] = 'L';
                            curr_cell = {curr_cell.row, curr_cell.col + 1};
                        } break;
                        default: {
                        } break;
                        }
                    }
                }
                std::cout << "YES\n"
                          << path.size() << '\n'
                          << path << '\n';
                std::exit(0);
            }

            to_explores.push(adj);
        }
    }
    std::cout << "NO\n";
}