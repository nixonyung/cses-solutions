#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

namespace {
using i32 = int_fast32_t;
using i64 = int_fast64_t;
using u8 = uint_fast8_t;
using u32 = uint_fast32_t;
using u64 = uint_fast64_t;

enum class VisitFrom : u8 {
    UNKNOWN,
    NIL, // used for starting cells
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

struct Pos {
    i64 row;
    i64 col;
};

struct PlayerState {
    u32 fastest_arrive_time;
    VisitFrom visit_from;
};
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    u32 height;
    u32 width;
    {
        std::cin >> height >> width;
    }

    auto board = std::vector<char>(height * width);
    Pos start;
    auto monster_fastest_arrive_times = std::vector<u32>(height * width, UINT32_MAX);
    auto monster_queue = std::queue<Pos>();
    {
        for (i32 row = 0; std::cmp_less(row, height); row++) {
            for (i32 col = 0; std::cmp_less(col, width); col++) {
                auto &cell = board[row * width + col];

                std::cin >> cell;
                if (cell == 'A') {
                    if (
                        row == 0 || std::cmp_equal(row, height - 1) ||
                        col == 0 || std::cmp_equal(col, width - 1)
                    ) {
                        std::cout << "YES\n0\n\n";
                        std::exit(0);
                    }
                    start = {row, col};
                } else if (cell == 'M') {
                    monster_fastest_arrive_times[row * width + col] = 0;
                    monster_queue.push({row, col});
                }
            }
        }
    }
    while (!monster_queue.empty()) {
        auto const pos = monster_queue.front();
        monster_queue.pop();
        for (auto const &adj : {
                 Pos{pos.row,     pos.col - 1},
                 Pos{pos.row,     pos.col + 1},
                 Pos{pos.row - 1, pos.col    },
                 Pos{pos.row + 1, pos.col    },
        }) {
            if (
                adj.row < 0 || std::cmp_greater_equal(adj.row, height) ||
                adj.col < 0 || std::cmp_greater_equal(adj.col, width) ||
                board[adj.row * width + adj.col] == '#' ||
                monster_fastest_arrive_times[adj.row * width + adj.col] <= monster_fastest_arrive_times[pos.row * width + pos.col] + 1
            ) continue;
            monster_fastest_arrive_times[adj.row * width + adj.col] = monster_fastest_arrive_times[pos.row * width + pos.col] + 1;
            monster_queue.push(adj);
        }
    }

    auto path = std::string();
    {
        auto states = std::vector<PlayerState>(height * width, {UINT32_MAX, VisitFrom::UNKNOWN});
        auto player_stack = std::stack<Pos>();
        states[start.row * width + start.col] = {0, VisitFrom::NIL};
        player_stack.push(start);
        while (!player_stack.empty()) {
            auto const pos = player_stack.top();
            player_stack.pop();
            for (auto const &[adj, visit_from] : {
                     std::tuple{Pos{pos.row + 1, pos.col}, VisitFrom::UP   },
                     std::tuple{Pos{pos.row - 1, pos.col}, VisitFrom::DOWN },
                     std::tuple{Pos{pos.row, pos.col + 1}, VisitFrom::LEFT },
                     std::tuple{Pos{pos.row, pos.col - 1}, VisitFrom::RIGHT},
            }) {
                if (
                    adj.row < 0 || std::cmp_greater_equal(adj.row, height) ||
                    adj.col < 0 || std::cmp_greater_equal(adj.col, width) ||
                    board[adj.row * width + adj.col] == '#' ||
                    states[adj.row * width + adj.col].fastest_arrive_time < states[pos.row * width + pos.col].fastest_arrive_time + 1 ||
                    monster_fastest_arrive_times[adj.row * width + adj.col] <= states[pos.row * width + pos.col].fastest_arrive_time + 1
                ) continue;
                states[adj.row * width + adj.col] = {states[pos.row * width + pos.col].fastest_arrive_time + 1, visit_from};
                player_stack.push(adj);

                if (
                    adj.row == 0 || std::cmp_equal(adj.row, height - 1) ||
                    adj.col == 0 || std::cmp_equal(adj.col, width - 1)
                ) {
                    auto curr = adj;
                    while (states[curr.row * width + curr.col].visit_from != VisitFrom::NIL) {
                        switch (states[curr.row * width + curr.col].visit_from) {
                        case VisitFrom::UP: {
                            path += 'D';
                            curr.row--;
                        } break;
                        case VisitFrom::DOWN: {
                            path += 'U';
                            curr.row++;
                        } break;
                        case VisitFrom::LEFT: {
                            path += 'R';
                            curr.col--;
                        } break;
                        case VisitFrom::RIGHT: {
                            path += 'L';
                            curr.col++;
                        } break;
                        default: {
                        } break;
                        }
                    }
                    std::ranges::reverse(path);
                    std::cout << "YES\n"
                              << path.size() << '\n'
                              << path << '\n';
                    std::exit(0);
                }
            }
        }
    }
    std::cout << "NO\n";
}