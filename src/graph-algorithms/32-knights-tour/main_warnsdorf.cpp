#include "io.hpp"
#include "primitives.hpp"
#include <queue>
#include <stack>
#include <tuple>
#include <utility>
#include <vector>

// (ref.) [Knight's tour - Warnsdorf's rule](https://www.wikiwand.com/en/articles/Knight%27s_tour#Warnsdorf%27s_rule)
// correct implementation but outputs are different from tests
int main() {
    enable_fast_io();

    const U32 BOARD_SIZE = 8;
    const U32 &NUM_CELLS = BOARD_SIZE * BOARD_SIZE;
    const auto DELTAS = std::vector<std::tuple<I8, I8>>{
        {-2, -1},
        {-2, 1 },
        {-1, -2},
        {-1, 2 },
        {1,  -2},
        {1,  2 },
        {2,  -1},
        {2,  1 },
    };
    auto NEXTSS = std::vector<std::vector<U32>>(NUM_CELLS);
    {
        for (I32 row = 0; std::cmp_less(row, BOARD_SIZE); row++) {
            for (I32 col = 0; std::cmp_less(col, BOARD_SIZE); col++) {
                for (auto const &[DELTA_ROW, DELTA_COL] : DELTAS) {
                    auto const next_row = row + DELTA_ROW;
                    auto const next_col = col + DELTA_COL;
                    if (
                        next_row < 0 || std::cmp_greater_equal(next_row, BOARD_SIZE) ||
                        next_col < 0 || std::cmp_greater_equal(next_col, BOARD_SIZE)
                    ) continue;
                    NEXTSS[row * BOARD_SIZE + col].push_back(next_row * BOARD_SIZE + next_col);
                }
            }
        }
    }

    // peronsal preference: transform to 0-indexed
    auto start_col = read<U32>() - 1;
    auto start_row = read<U32>() - 1;

    auto visited_ats = std::vector<U32>(NUM_CELLS);
    {
        auto path = std::stack<U32>();
        {
            struct ToVisit {
                U32 epoch;
                U32 pos;
                U32 out_degree;
            };
            auto to_visits = std::priority_queue<
                ToVisit,
                std::vector<ToVisit>,
                decltype(BINARY_FN(lhs, rhs) {
                    return lhs.epoch != rhs.epoch ? lhs.epoch < rhs.epoch            // prioritize higher (i.e. more recent) epoch
                                                  : lhs.out_degree > rhs.out_degree; // else prioritize lower out_degree as per Warnsdorf's rule
                })>();
            auto visiteds = std::vector<bool>(NUM_CELLS, false);

            to_visits.push({0, start_row * BOARD_SIZE + start_col, 0});
            while (!to_visits.empty()) {
                auto const [epoch, curr, out_degree] = to_visits.top();
                to_visits.pop();
                while (path.size() > epoch) {
                    visiteds[path.top()] = false;
                    path.pop();
                }
                path.push(curr);
                visiteds[curr] = true;

                for (auto const &next : NEXTSS[curr]) {
                    if (visiteds[next]) continue;
                    if (epoch + 1 == NUM_CELLS - 1) {
                        path.push(next);
                        goto PATH_INIT_END;
                    }
                    U32 out_degree = 0;
                    {
                        for (auto const &next_next : NEXTSS[next]) {
                            if (visiteds[next_next]) continue;
                            out_degree++;
                        }
                    }
                    to_visits.push({epoch + 1, next, out_degree});
                }
            }
        PATH_INIT_END:;
        }

        U32 epoch = NUM_CELLS;
        while (!path.empty()) {
            visited_ats[path.top()] = epoch--;
            path.pop();
        }
    }
    for (U32 row = 0; row < BOARD_SIZE; row++) {
        for (U32 col = 0; col < BOARD_SIZE; col++) {
            std::cout << visited_ats[row * BOARD_SIZE + col] << ' ';
        }
        std::cout << '\n';
    }
}