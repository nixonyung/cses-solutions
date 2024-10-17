#include "io.hpp"
#include "primitives.hpp"
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>

// (ref.) [Kosaraju's algorithm](https://www.wikiwand.com/en/articles/Kosaraju%27s_algorithm)
int main() {
    enable_fast_io();

    auto num_persons = read<U32>();
    auto num_toppings = read<U32>();
    auto implications = std::vector<std::vector<U32>>(num_toppings * 2); // -i has implications[i*2], +i has implications[i*2 + 1]
    auto implication_revs = std::vector<std::vector<U32>>(num_toppings * 2);
    {
        for (U32 i = 0; i < num_persons; i++) {
            auto sign1 = read<char>();
            auto topping1 = read<U32>() - 1; // peronsal preference: transform to 0-indexed
            auto sign2 = read<char>();
            auto topping2 = read<U32>() - 1; // peronsal preference: transform to 0-indexed

            implications[topping1 * 2 + (sign1 == '-')].push_back(topping2 * 2 + (sign2 == '+'));
            implication_revs[topping2 * 2 + (sign2 == '+')].push_back(topping1 * 2 + (sign1 == '-'));
            implications[topping2 * 2 + (sign2 == '-')].push_back(topping1 * 2 + (sign1 == '+'));
            implication_revs[topping1 * 2 + (sign1 == '+')].push_back(topping2 * 2 + (sign2 == '-'));
        }
    }

    auto scc_ids = std::vector<U32>(num_toppings * 2, UINT_MAX);
    U32 num_sccs = 0;
    {
        auto nodes_sorted = std::stack<U32>();
        auto to_visits = std::stack<U32>(); // preallocate memory
        {
            enum Phase : unsigned char {
                EXPLORE,
                BACKTRACKING,
                DONE,
            };
            auto phases = std::vector<Phase>(num_toppings * 2, Phase::EXPLORE);
            for (U32 i = 0; i < num_toppings * 2; i++) {
                if (phases[i] != Phase::EXPLORE) continue;
                to_visits.push(i);
                while (!to_visits.empty()) {
                    auto const curr = to_visits.top();
                    to_visits.pop();
                    if (phases[curr] == Phase::DONE) continue;

                    if (phases[curr] == Phase::BACKTRACKING) {
                        phases[curr] = Phase::DONE;
                        nodes_sorted.push(curr);
                        continue;
                    }

                    phases[curr] = Phase::BACKTRACKING;
                    to_visits.push(curr);
                    for (auto const &adj : implications[curr]) {
                        if (phases[adj] != Phase::EXPLORE) continue;
                        to_visits.push(adj);
                    }
                }
            }
        }
        {
            while (!nodes_sorted.empty()) {
                auto const node = nodes_sorted.top();
                nodes_sorted.pop();
                if (scc_ids[node] != UINT_MAX) continue;

                num_sccs++;
                to_visits.push(node);
                while (!to_visits.empty()) {
                    auto const curr = to_visits.top();
                    to_visits.pop();
                    if (scc_ids[curr] != UINT_MAX) continue;

                    scc_ids[curr] = num_sccs;

                    for (auto const &adj : implication_revs[curr]) {
                        if (scc_ids[adj] != UINT_MAX) continue;
                        to_visits.push(adj);
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
        // Korasaju's algorithm labels SCC with LOWER topological order first
        // so we pick the choice with higher `scc_id`
        std::cout << ((scc_ids[i * 2] > scc_ids[i * 2 + 1]) ? "- " : "+ ");
    }
    std::cout << "\n";
}