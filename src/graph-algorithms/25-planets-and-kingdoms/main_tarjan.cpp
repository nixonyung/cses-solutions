#include "io.hpp"
#include "k_bitset.hpp"
#include "primitives.hpp"
#include <cstdlib>
#include <iostream>
#include <ranges>
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
    }

    auto kingdom_ids = std::vector<U32>(num_planets, UINT_MAX);
    U32 num_kingdoms = 0;
    {
        enum Phase : unsigned char {
            EXPLORE,
            BACKTRACKING,
            DONE,
        };
        auto phases = KBitset<2>(num_planets, Phase::EXPLORE);

        struct State {
            U32 explored_at_epoch;
            U32 min_adj_explored_at_epoch;
            bool can_extract;
        };
        auto states = std::vector<State>(num_planets, {UINT_MAX, UINT_MAX, false});
        {
            auto to_visits = std::stack<U32>();
            auto can_extracts = std::stack<U32>();

            U32 epoch = 0;
            for (U32 i = 0; i < num_planets; i++) {
                if (phases[i] != Phase::EXPLORE) continue;
                to_visits.push(i);
                while (!to_visits.empty()) {
                    auto const curr = to_visits.top();
                    to_visits.pop();
                    if (phases[curr] == Phase::DONE) continue;

                    if (phases[curr] == Phase::EXPLORE) {
                        phases[curr] = Phase::BACKTRACKING;
                        states[curr].explored_at_epoch = states[curr].min_adj_explored_at_epoch = epoch++;
                        states[curr].can_extract = true;
                        can_extracts.push(curr);

                        to_visits.push(curr);
                        for (auto const &adj : adjss[curr] | std::views::reverse) { // reverse adjs to match test outputs
                            if (phases[adj] != Phase::EXPLORE) continue;
                            to_visits.push(adj);
                        }
                    } else {
                        phases[curr] = Phase::DONE;

                        for (auto const &adj : adjss[curr]) {
                            if (!states[adj].can_extract) continue;
                            states[curr].min_adj_explored_at_epoch = std::min(states[curr].min_adj_explored_at_epoch, states[adj].min_adj_explored_at_epoch);
                        }
                        if (states[curr].min_adj_explored_at_epoch == states[curr].explored_at_epoch) {
                            num_kingdoms++;
                            {
                                U32 top;
                                do {
                                    top = can_extracts.top();
                                    can_extracts.pop();
                                    states[top].min_adj_explored_at_epoch = states[curr].min_adj_explored_at_epoch;
                                    states[top].can_extract = false;
                                    kingdom_ids[top] = num_kingdoms - 1;
                                } while (top != curr);
                            }
                        }
                    }
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