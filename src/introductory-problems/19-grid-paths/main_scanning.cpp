#include <iostream>
#include <string>
#include <vector>

namespace {
const unsigned BOARD_SIZE = 7;
const unsigned NUM_CELLS = BOARD_SIZE * BOARD_SIZE;
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str;
    {
        std::cin >> str;
    }

    auto visiteds = std::vector<bool>(NUM_CELLS, false);
    auto can_visit = [&visiteds](
                         unsigned row,
                         unsigned col
                     ) -> bool {
        return row < BOARD_SIZE
               && col < BOARD_SIZE
               && !visiteds[row * BOARD_SIZE + col];
    };
    auto dfs = [&str, &visiteds, &can_visit](
                   unsigned action_idx,
                   unsigned row,
                   unsigned col
               ) -> unsigned {
        auto impl = [&str, &visiteds, &can_visit](
                        auto impl_ref,
                        unsigned action_idx,
                        unsigned row,
                        unsigned col
                    ) -> unsigned {
            if (row == 6 && col == 0) return action_idx == 48;
            // (ref.) [CSES - Grid Paths - Optimization 3](https://usaco.guide/problems/cses-1625-grid-paths/solution#optimization-3)
            switch ((can_visit(row, col + 1) << 3)
                    + (can_visit(row, col - 1) << 2)
                    + (can_visit(row - 1, col) << 1)
                    + can_visit(row + 1, col)) {
            case 0b0011:
            case 0b1100:
                return 0;
            }
            // (ref.) [CSES - Grid Paths - Optimization 4](https://usaco.guide/problems/cses-1625-grid-paths/solution#optimization-4)
            char action_to_avoid_dead_end = '?';
            {
                if (
                    !(row == 6 && col - 1 == 0)
                    && can_visit(row, col - 1)         // L
                    && (!can_visit(row, col - 2)       // LL
                        + !can_visit(row - 1, col - 1) // LU
                        + !can_visit(row + 1, col - 1) // LD
                       ) == 2
                ) {
                    if (action_to_avoid_dead_end != '?') return 0;
                    action_to_avoid_dead_end = 'L';
                }
                if (
                    !(row == 6 && col + 1 == 0)
                    && can_visit(row, col + 1)         // R
                    && (!can_visit(row, col + 2)       // RR
                        + !can_visit(row - 1, col + 1) // RU
                        + !can_visit(row + 1, col + 1) // RD
                       ) == 2
                ) {
                    if (action_to_avoid_dead_end != '?') return 0;
                    action_to_avoid_dead_end = 'R';
                }
                if (
                    !(row - 1 == 6 && col == 0)
                    && can_visit(row - 1, col)         // U
                    && (!can_visit(row - 1, col - 1) + // UL
                        !can_visit(row - 1, col + 1) + // UR
                        !can_visit(row - 2, col)       // UU
                       ) == 2
                ) {
                    if (action_to_avoid_dead_end != '?') return 0;
                    action_to_avoid_dead_end = 'U';
                }
                if (
                    !(row + 1 == 6 && col == 0)
                    && can_visit(row + 1, col)         // D
                    && (!can_visit(row + 1, col - 1) + // DL
                        !can_visit(row + 1, col + 1) + // DR
                        !can_visit(row + 2, col)       // DD
                       ) == 2
                ) {
                    if (action_to_avoid_dead_end != '?') return 0;
                    action_to_avoid_dead_end = 'D';
                }
            }

            visiteds[row * 7 + col] = true;
            unsigned num_configurations = 0;
            {
                // move col first for better caching as it is likely to find elements at the same row in the cache lines
                if (
                    (str[action_idx] == 'L' || str[action_idx] == '?')
                    && (action_to_avoid_dead_end == 'L' || action_to_avoid_dead_end == '?')
                    && can_visit(row, col - 1)
                ) num_configurations += impl_ref(impl_ref, action_idx + 1, row, col - 1);
                if (
                    (str[action_idx] == 'R' || str[action_idx] == '?')
                    && (action_to_avoid_dead_end == 'R' || action_to_avoid_dead_end == '?')
                    && can_visit(row, col + 1)
                ) num_configurations += impl_ref(impl_ref, action_idx + 1, row, col + 1);
                // move up first for better caching as revisiting rows is more likely to have cache hits
                if (
                    (str[action_idx] == 'U' || str[action_idx] == '?')
                    && (action_to_avoid_dead_end == 'U' || action_to_avoid_dead_end == '?')
                    && can_visit(row - 1, col)
                ) num_configurations += impl_ref(impl_ref, action_idx + 1, row - 1, col);
                if (
                    (str[action_idx] == 'D' || str[action_idx] == '?')
                    && (action_to_avoid_dead_end == 'D' || action_to_avoid_dead_end == '?')
                    && can_visit(row + 1, col)
                ) num_configurations += impl_ref(impl_ref, action_idx + 1, row + 1, col);
            }
            visiteds[row * 7 + col] = false;
            return num_configurations;
        };
        return impl(impl, action_idx, row, col);
    };
    std::cout << dfs(0, 0, 0) << '\n';
}