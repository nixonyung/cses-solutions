#include "dfs.hpp" // this version is using my experimental custom DFS helper library
#include "io.hpp"
#include "primitives.hpp"
#include <cstdlib>
#include <stack>
#include <vector>

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
        struct State {
            U32 explored_at_epoch;
            U32 min_adj_explored_at_epoch; // the "lowlink" value, should also consider the node itself
            bool can_extract;
        };
        auto states = std::vector<State>(num_toppings * 2, {UINT_MAX, UINT_MAX, false});
        {
            auto dfs = DFS(num_toppings * 2, implications);
            auto to_extracts = std::stack<USize>();
            U32 epoch = 0;

            for (U32 i = 0; i < num_toppings * 2; i++) {
                dfs.push(i);
                for (auto to_visit = dfs.pop(); to_visit.id != UINT_MAX; to_visit = dfs.pop()) {
                    auto const &[curr, phase] = to_visit;

                    if (phase == DFS<>::Phase::BACKTRACKING) {
                        for (auto const &adj : implications[curr]) {
                            if (!states[adj].can_extract) continue;
                            states[curr].min_adj_explored_at_epoch = std::min(states[curr].min_adj_explored_at_epoch, states[adj].min_adj_explored_at_epoch);
                        }
                        if (states[curr].min_adj_explored_at_epoch == states[curr].explored_at_epoch) {
                            num_sccs++;
                            {
                                USize top;
                                do {
                                    top = to_extracts.top();
                                    to_extracts.pop();
                                    states[top].min_adj_explored_at_epoch = states[curr].min_adj_explored_at_epoch;
                                    states[top].can_extract = false;
                                    scc_ids[top] = num_sccs - 1;
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
    for (U32 i = 0; i < num_toppings; i++) {
        if (scc_ids[i * 2] == scc_ids[i * 2 + 1]) {
            std::cout << "IMPOSSIBLE\n";
            std::exit(0);
        }
    }
    for (U32 i = 0; i < num_toppings; i++) {
        // Tarjan's algorithm labels SCC with HIGHER topological order first,
        // so we pick the choice with lower `scc_id`
        std::cout << ((scc_ids[i * 2] < scc_ids[i * 2 + 1]) ? "- " : "+ ");
    }
    std::cout << "\n";
}