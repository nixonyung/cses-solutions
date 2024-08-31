#define ENABLE_PRUNE_BY_IMPOSSIBLE_PARTITIONING
#define ENABLE_PRUNE_BY_AVOIDING_DEAD_ENDS

#include <bitset>
#include <iostream>
#include <vector>

template <std::size_t NUM_CELLS>
inline auto can_visit(int i, int j, std::bitset<NUM_CELLS> &visited) {
    return (0 <= i && i < 7)
           && (0 <= j && j < 7)
           && !visited[i * 7 + j];
}

template <std::size_t NUM_CELLS>
auto dfs(int i, int j, int action_idx, std::bitset<NUM_CELLS> &visited, std::vector<char> &s) -> int {
    if ((i == 6 && j == 0) || action_idx == 48) {
        return (i == 6 && j == 0) && action_idx == 48;
    }

#ifdef ENABLE_PRUNE_BY_IMPOSSIBLE_PARTITIONING
    // (ref.) [CSES - Grid Paths - Optimization 3](https://usaco.guide/problems/cses-1625-grid-paths/solution#optimization-3)
    int det = (can_visit(i, j + 1, visited) << 3)
              + (can_visit(i, j - 1, visited) << 2)
              + (can_visit(i - 1, j, visited) << 1)
              + can_visit(i + 1, j, visited);
    if (det == 0b0011 || det == 0b1100) {
        return 0;
    }
#endif

    char action_to_avoid_dead_end = '?';
#ifdef ENABLE_PRUNE_BY_AVOIDING_DEAD_ENDS
    // (ref.) [CSES - Grid Paths - Optimization 4](https://usaco.guide/problems/cses-1625-grid-paths/solution#optimization-4)
    if (
        !(i == 6 && j + 1 == 0)
        && can_visit(i, j + 1, visited)         // R
        && (!can_visit(i, j + 2, visited)       // RR
            + !can_visit(i - 1, j + 1, visited) // RU
            + !can_visit(i + 1, j + 1, visited) // RD
           ) == 2
    ) {
        if (action_to_avoid_dead_end != '?') {
            return 0;
        }
        action_to_avoid_dead_end = 'R';
    }
    if (
        !(i == 6 && j - 1 == 0)
        && can_visit(i, j - 1, visited)         // L
        && (!can_visit(i, j - 2, visited)       // LL
            + !can_visit(i - 1, j - 1, visited) // LU
            + !can_visit(i + 1, j - 1, visited) // LD
           ) == 2
    ) {
        if (action_to_avoid_dead_end != '?') {
            return 0;
        }
        action_to_avoid_dead_end = 'L';
    }
    if (
        !(i - 1 == 6 && j == 0)
        && can_visit(i - 1, j, visited)         // U
        && (!can_visit(i - 1, j + 1, visited)   // UR
            + !can_visit(i - 1, j - 1, visited) // UL
            + !can_visit(i - 2, j, visited)     // UU
           ) == 2
    ) {
        if (action_to_avoid_dead_end != '?') {
            return 0;
        }
        action_to_avoid_dead_end = 'U';
    }
    if (
        !(i + 1 == 6 && j == 0)
        && can_visit(i + 1, j, visited)         // D
        && (!can_visit(i + 1, j + 1, visited)   // DR
            + !can_visit(i + 1, j - 1, visited) // DL
            + !can_visit(i + 2, j, visited)     // DD
           ) == 2
    ) {
        if (action_to_avoid_dead_end != '?') {
            return 0;
        }
        action_to_avoid_dead_end = 'D';
    }
#endif

    auto ans = 0;
    visited[i * 7 + j] = true;
    // move col first for better caching: elements in the same row are likely to fit into cache lines
    if (
        (s[action_idx] == 'R' || s[action_idx] == '?')
        && (action_to_avoid_dead_end == 'R' || action_to_avoid_dead_end == '?')
        && can_visit(i, j + 1, visited)
    ) {
        ans += dfs(i, j + 1, action_idx + 1, visited, s);
    }
    if (
        (s[action_idx] == 'L' || s[action_idx] == '?')
        && (action_to_avoid_dead_end == 'L' || action_to_avoid_dead_end == '?')
        && can_visit(i, j - 1, visited)
    ) {
        ans += dfs(i, j - 1, action_idx + 1, visited, s);
    }
    // move up first for better caching: as we start from row 0, rows with smaller indices are more likely to have cache hits
    if (
        (s[action_idx] == 'U' || s[action_idx] == '?')
        && (action_to_avoid_dead_end == 'U' || action_to_avoid_dead_end == '?')
        && can_visit(i - 1, j, visited)
    ) {
        ans += dfs(i - 1, j, action_idx + 1, visited, s);
    }
    if (
        (s[action_idx] == 'D' || s[action_idx] == '?')
        && (action_to_avoid_dead_end == 'D' || action_to_avoid_dead_end == '?')
        && can_visit(i + 1, j, visited)
    ) {
        ans += dfs(i + 1, j, action_idx + 1, visited, s);
    }
    visited[i * 7 + j] = false;
    return ans;
}

int main() {
    auto const NUM_CELLS = 49;

    auto s = std::vector<char>(NUM_CELLS - 1);
    for (auto &ch : s) {
        std::cin >> ch;
    }

    auto visited = std::bitset<NUM_CELLS>();
    auto ans = dfs<NUM_CELLS>(0, 0, 0, visited, s);
    std::cout << ans << '\n';
}