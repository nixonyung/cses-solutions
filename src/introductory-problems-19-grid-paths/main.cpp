#define ENABLE_PRUNE_BY_IMPOSSIBLE_PARTITIONING
#define ENABLE_PRUNE_BY_AVOIDING_DEAD_ENDS

#include <cstdio>

inline bool can_visit(int i, int j, bool visited[]) {
    return (0 <= i && i < 7) && (0 <= j && j < 7) && !visited[i * 7 + j];
}

int dfs(int i,
        int j,
        int action_idx,
        bool visited[],
        char s[]) {
    if ((i == 6 && j == 0) || action_idx == 48) {
        return (i == 6 && j == 0) && action_idx == 48;
    }

#ifdef ENABLE_PRUNE_BY_IMPOSSIBLE_PARTITIONING
    // (ref.) [CSES - Grid Paths - Optimization 3](https://usaco.guide/problems/cses-1625-grid-paths/solution#optimization-3)
    int det = (can_visit(i, j + 1, visited) << 3) +
              (can_visit(i, j - 1, visited) << 2) +
              (can_visit(i - 1, j, visited) << 1) +
              can_visit(i + 1, j, visited);
    if (det == 0b0011 || det == 0b1100) {
        return 0;
    }
#endif

    char action_to_avoid_dead_end = '?';
#ifdef ENABLE_PRUNE_BY_AVOIDING_DEAD_ENDS
    // (ref.) [CSES - Grid Paths - Optimization 4](https://usaco.guide/problems/cses-1625-grid-paths/solution#optimization-4)
    if (
        !(i == 6 && j + 1 == 0) &&
        can_visit(i, j + 1, visited) &&             // R
        (!can_visit(i, j + 2, visited) +            // RR
         !can_visit(i - 1, j + 1, visited) +        // RU
         !can_visit(i + 1, j + 1, visited)) == 2) { // RD
        if (action_to_avoid_dead_end != '?') {
            return 0;
        }
        action_to_avoid_dead_end = 'R';
    } else if (
        !(i == 6 && j - 1 == 0) &&
        can_visit(i, j - 1, visited) &&             // L
        (!can_visit(i, j - 2, visited) +            // LL
         !can_visit(i - 1, j - 1, visited) +        // LU
         !can_visit(i + 1, j - 1, visited)) == 2) { // LD
        if (action_to_avoid_dead_end != '?') {
            return 0;
        }
        action_to_avoid_dead_end = 'L';
    } else if (
        !(i - 1 == 6 && j == 0) &&
        can_visit(i - 1, j, visited) &&         // U
        (!can_visit(i - 1, j + 1, visited) +    // UR
         !can_visit(i - 1, j - 1, visited) +    // UL
         !can_visit(i - 2, j, visited)) == 2) { // UU
        if (action_to_avoid_dead_end != '?') {
            return 0;
        }
        action_to_avoid_dead_end = 'U';
    } else if (
        !(i + 1 == 6 && j == 0) &&
        can_visit(i + 1, j, visited) &&         // D
        (!can_visit(i + 1, j + 1, visited) +    // DR
         !can_visit(i + 1, j - 1, visited) +    // DL
         !can_visit(i + 2, j, visited)) == 2) { // DD
        if (action_to_avoid_dead_end != '?') {
            return 0;
        }
        action_to_avoid_dead_end = 'D';
    }
#endif

    // printf("%d %d %d %c\n", i, j, action_idx, action_to_avoid_dead_end); // debug
    visited[i * 7 + j] = true;
    int ans = 0;
    // move col first for better caching: elements in the same row are likely to fit into cache lines
    if ((s[action_idx] == 'R' || s[action_idx] == '?') && (action_to_avoid_dead_end == 'R' || action_to_avoid_dead_end == '?') && can_visit(i, j + 1, visited)) {
        ans += dfs(i, j + 1, action_idx + 1, visited, s);
    }
    if ((s[action_idx] == 'L' || s[action_idx] == '?') && (action_to_avoid_dead_end == 'L' || action_to_avoid_dead_end == '?') && can_visit(i, j - 1, visited)) {
        ans += dfs(i, j - 1, action_idx + 1, visited, s);
    }
    // move up first for better caching: as we start from row 0, rows with smaller indices are more likely to have cache hits
    if ((s[action_idx] == 'U' || s[action_idx] == '?') && (action_to_avoid_dead_end == 'U' || action_to_avoid_dead_end == '?') && can_visit(i - 1, j, visited)) {
        ans += dfs(i - 1, j, action_idx + 1, visited, s);
    }
    if ((s[action_idx] == 'D' || s[action_idx] == '?') && (action_to_avoid_dead_end == 'D' || action_to_avoid_dead_end == '?') && can_visit(i + 1, j, visited)) {
        ans += dfs(i + 1, j, action_idx + 1, visited, s);
    }
    visited[i * 7 + j] = false;
    return ans;
}

int main() {
    char s[49];
    scanf("%s", s);

    bool visited[49];
    for (int i = 0; i < 49; i++) {
        visited[i] = false;
    }

    printf("%d\n", dfs(0, 0, 0, visited, s));
}