#include "io.hpp"
#include "primitives.hpp"
#include <algorithm>
#include <map>
#include <queue>
#include <ranges>
#include <stack>
#include <vector>

// (ref.) [Maximum flow - Dinic's algorithm](https://cp-algorithms.com/graph/dinic.html)
int main() {
    enable_fast_io();

    auto num_computers = read<U32>();
    auto num_connections = read<U32>();
    auto capacityss = std::vector<std::map<U32, U64>>(num_computers);
    {
        for (U32 i = 0; i < num_connections; i++) {
            // peronsal preference: transform to 0-indexed
            auto start = read<U32>() - 1;
            auto end = read<U32>() - 1;
            auto capacity = read<U32>();
            capacityss[start][end] += capacity; // combine multiple edges
            capacityss[end][start] += 0;        // ensure reverse edge exist
        }
    }

    U64 max_flow = 0;
    {
        auto levels = std::vector<U32>(num_computers);
        auto bfs = std::queue<U32>();
        struct DFSToVisit {
            U32 path_len;
            U32 city_id;
            U64 flow;
        };
        auto dfs = std::stack<DFSToVisit>();
        auto dfs_path = std::vector<U32>();

        U64 delta_max_flow;
        do {
            delta_max_flow = 0;

            std::ranges::fill(levels, UINT_MAX);
            levels[0] = 0;
            {
                bfs.push(0);
                while (!bfs.empty()) {
                    auto const curr = bfs.front();
                    bfs.pop();

                    for (auto const &[next, capacity] : capacityss[curr]) {
                        if (capacity == 0 || levels[next] != UINT_MAX) continue;
                        levels[next] = levels[curr] + 1;
                        bfs.push(next);
                    }
                }
            }
            if (levels[num_computers - 1] == UINT_MAX) break;

            while (!dfs.empty()) dfs.pop();
            dfs_path.clear();
            {
                dfs.push({0, 0, ULONG_MAX});
                while (!dfs.empty()) {
                    auto const [path_len, curr, flow] = dfs.top();
                    dfs.pop();
                    dfs_path.resize(path_len);
                    dfs_path.push_back(curr);

                    for (auto const &[next, capacity] : capacityss[curr]) {
                        auto const new_flow = std::min(flow, capacity);
                        if (
                            new_flow == 0 ||
                            levels[next] != levels[curr] + 1 ||
                            levels[next] > levels[num_computers - 1]
                        ) continue;
                        if (next == num_computers - 1) {
                            delta_max_flow = new_flow;

                            U32 curr = next;
                            for (auto const prev : dfs_path | std::views::reverse) {
                                capacityss[prev][curr] -= delta_max_flow;
                                capacityss[curr][prev] += delta_max_flow;
                                curr = prev;
                            }
                            goto DELTA_MAX_FLOW_FOUND;
                        }
                        dfs.push({path_len + 1, next, new_flow});
                    }
                }
            }
        DELTA_MAX_FLOW_FOUND:
            max_flow += delta_max_flow;
        } while (delta_max_flow != 0);
    }
    std::cout << max_flow << '\n';
}