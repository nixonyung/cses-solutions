#include "io.hpp"
#include "primitives.hpp"
#include <cstdlib>
#include <ranges>
#include <stack>
#include <vector>

// (ref.) [Eulerian path](https://cp-algorithms.com/graph/euler_path.html)
// (ref.) [Eulerian path - Properties](https://www.wikiwand.com/en/articles/Eulerian_path#Properties)
// (ref.) [Hierholzer's algorithm](https://www.wikiwand.com/en/articles/Eulerian_path#Hierholzer%27s_algorithm)
// correct implementation but outputs are different from tests
int main() {
    enable_fast_io();

    auto num_levels = read<U32>();
    auto num_teleporters = read<U32>();
    auto nextss = std::vector<std::vector<U32>>(num_levels);
    {
        auto out_degrees = std::vector<U32>(num_levels, 0);
        auto in_degrees = std::vector<U32>(num_levels, 0);

        for (U32 i = 0; i < num_teleporters; i++) {
            // peronsal preference: transform to 0-indexed
            auto start = read<U32>() - 1;
            auto end = read<U32>() - 1;
            nextss[start].push_back(end);
            out_degrees[start]++;
            in_degrees[end]++;
        }

        if (
            out_degrees[0] != in_degrees[0] + 1 ||
            out_degrees[num_levels - 1] + 1 != in_degrees[num_levels - 1]
        ) {
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }
        for (U32 i = 1; i < num_levels - 1; i++) {
            if (out_degrees[i] != in_degrees[i]) {
                std::cout << "IMPOSSIBLE\n";
                return 0;
            }
        }
    }

    auto path = std::vector<U32>();
    {
        auto to_visits = std::stack<U32>();
        auto next_idxs = std::vector<U32>(num_levels, 0);

        to_visits.push(0);
        while (!to_visits.empty()) {
            auto const curr = to_visits.top();
            if (next_idxs[curr] == nextss[curr].size()) { // 2 choices for each node (append 0 or 1), so `curr_edge_idx` == 2 means no more unused choices
                path.push_back(curr);
                to_visits.pop();
                continue;
            }
            to_visits.push(nextss[curr][next_idxs[curr]++]);
        }
    }
    if (path.size() != num_teleporters + 1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (auto const id : path | std::views::reverse) {
        std::cout << id + 1 << ' ';
    }
    std::cout << '\n';
}