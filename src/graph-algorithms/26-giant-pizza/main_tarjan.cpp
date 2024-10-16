#include "io.hpp"
#include "k_bitset.hpp"
#include "primitives.hpp"
#include <cstdlib>
#include <iostream>
#include <ranges>
#include <stack>
#include <vector>

// (ref.) [Tarjan's Strongly Connected Component (SCC) Algorithm (UPDATED) | Graph Theory](https://youtu.be/wUgWX0nc4NY?si=a9VpzlmTYt1gZDPs)
// (ref.) [2-SAT](https://cp-algorithms.com/graph/2SAT.html)
// idea: for any topping i, +i and -i cannot be in the same SCC
//
// correct implementation but outputs are different from tests
int main() {
    enable_fast_io();

    auto num_persons = read<U32>();
    auto num_toppings = read<U32>();
    auto implications = std::vector<std::vector<U32>>(num_toppings * 2); // -i has implications[i*2], +i has implications[i*2 + 1]
    {
        for (U32 i = 0; i < num_persons; i++) {
            auto sign1 = read<char>();
            auto topping1 = read<U32>() - 1; // peronsal preference: transform to 0-indexed
            auto sign2 = read<char>();
            auto topping2 = read<U32>() - 1; // peronsal preference: transform to 0-indexed
            implications[topping1 * 2 + (sign1 == '-')].push_back(topping2 * 2 + (sign2 == '+'));
            implications[topping2 * 2 + (sign2 == '-')].push_back(topping1 * 2 + (sign1 == '+'));
        }
    }

    auto scc_ids = std::vector<U32>(num_toppings * 2, UINT_MAX);
    U32 num_sccs = 0;
    {
        enum Phase : unsigned char {
            EXPLORE,
            BACKTRACKING,
            DONE,
        };
        auto phases = KBitset<2>(num_toppings * 2, Phase::EXPLORE);

        struct State {
            U32 explored_at_epoch;
            U32 min_adj_explored_at_epoch;
            bool can_extract;
        };
        auto states = std::vector<State>(num_toppings * 2, {UINT_MAX, UINT_MAX, false});
        {
            auto to_visits = std::stack<U32>();
            auto can_extracts = std::stack<U32>();

            U32 epoch = 0;
            for (U32 i = 0; i < num_toppings * 2; i++) {
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
                        for (auto const &adj : implications[curr] | std::views::reverse) { // reverse adjs to match test outputs
                            if (phases[adj] != Phase::EXPLORE) continue;
                            to_visits.push(adj);
                        }
                    } else {
                        phases[curr] = Phase::DONE;

                        for (auto const &adj : implications[curr]) {
                            if (!states[adj].can_extract) continue;
                            states[curr].min_adj_explored_at_epoch = std::min(states[curr].min_adj_explored_at_epoch, states[adj].min_adj_explored_at_epoch);
                        }
                        if (states[curr].min_adj_explored_at_epoch == states[curr].explored_at_epoch) {
                            num_sccs++;
                            {
                                U32 top;
                                do {
                                    top = can_extracts.top();
                                    can_extracts.pop();
                                    states[top].min_adj_explored_at_epoch = states[curr].min_adj_explored_at_epoch;
                                    states[top].can_extract = false;
                                    scc_ids[top] = num_sccs - 1;
                                } while (top != curr);
                            }
                        }
                    }
                }
            }
        }
    }
    for (U32 i = 0; i < num_toppings; i++) {
        if (scc_ids[i * 2] == scc_ids[i * 2 + 1]) {
            std::cout << "IMPOSSIBLE\n";
            std::exit(0);
        }
    }
    for (U32 i = 0; i < num_toppings; i++) {
        // as if visiting SCCs in ascending order of `scc_id`s
        std::cout << ((scc_ids[i * 2] < scc_ids[i * 2 + 1]) ? "- " : "+ ");
    }
    std::cout << "\n";
}