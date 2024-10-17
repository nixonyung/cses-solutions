#include "dfs.hpp" // this version is using my experimental custom DFS helper library
#include "io.hpp"
#include "primitives.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>

// (ref.) [Tarjan's Strongly Connected Component (SCC) Algorithm (UPDATED) | Graph Theory](https://youtu.be/wUgWX0nc4NY?si=a9VpzlmTYt1gZDPs)
int main() {
    enable_fast_io();

    auto num_planets = read<U32>();
    auto num_routes = read<U32>();
    auto adjss = std::vector<std::vector<U32>>(num_planets);
    {
        for (U32 i = 0; i < num_routes; i++) {
            adjss[read<U32>() - 1].push_back(read<U32>() - 1); // peronsal preference: transform to 0-indexed
        }
        for (U32 i = 0; i < num_planets; i++) {
            std::ranges::reverse(adjss[i]); // to match test outputs
        }
    }

    auto kingdom_ids = std::vector<U32>(num_planets, UINT_MAX);
    U32 num_kingdoms = 0;
    {
        struct State {
            U32 explored_at_epoch;
            U32 min_adj_explored_at_epoch;
            bool can_extract;
        };
        auto states = std::vector<State>(num_planets, {UINT_MAX, UINT_MAX, false});
        {
            auto dfs = DFS(num_planets, adjss);
            auto to_extracts = std::stack<U32>();
            U32 epoch = 0;

            for (U32 i = 0; i < num_planets; i++) {
                dfs.push(i);
                for (auto to_visit = dfs.pop(); to_visit.id != UINT_MAX; to_visit = dfs.pop()) {
                    auto const &[curr, phase] = to_visit;

                    if (phase == DFS<>::Phase::BACKTRACKING) {
                        for (auto const &adj : adjss[curr]) {
                            if (!states[adj].can_extract) continue;
                            states[curr].min_adj_explored_at_epoch = std::min(states[curr].min_adj_explored_at_epoch, states[adj].min_adj_explored_at_epoch);
                        }
                        if (states[curr].min_adj_explored_at_epoch == states[curr].explored_at_epoch) {
                            num_kingdoms++;
                            {
                                U32 top;
                                do {
                                    top = to_extracts.top();
                                    to_extracts.pop();
                                    states[top].min_adj_explored_at_epoch = states[curr].min_adj_explored_at_epoch;
                                    states[top].can_extract = false;
                                    kingdom_ids[top] = num_kingdoms - 1;
                                } while (top != curr);
                            }
                        }
                        continue;
                    }
                    states[curr].explored_at_epoch = states[curr].min_adj_explored_at_epoch = epoch++;
                    states[curr].can_extract = true;
                    to_extracts.push(curr);
                }
            }
        }
    }
    std::cout << num_kingdoms << '\n';
    for (auto const &kingdom_id : kingdom_ids) {
        std::cout << num_kingdoms - kingdom_id << ' '; // invert kingdom_ids to match test outputs
    }
    std::cout << "\n";
}