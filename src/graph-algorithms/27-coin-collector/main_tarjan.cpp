#include "dfs.hpp"
#include "io.hpp"
#include "primitives.hpp"
#include <cstdlib>
#include <stack>
#include <vector>

int main() {
    enable_fast_io();

    auto num_rooms = read<USize>();
    auto num_tunnels = read<USize>();

    auto num_coins = std::vector<U32>(num_rooms);
    auto nextss = std::vector<std::vector<U32>>(num_rooms);
    {
        for (U32 i = 0; i < num_rooms; i++) {
            num_coins[i] = read<U32>();
        }
        for (U32 i = 0; i < num_tunnels; i++) {
            nextss[read<U32>() - 1].push_back(read<U32>() - 1); // peronsal preference: transform to 0-indexed
        }
    }

    auto scc_ids = std::vector<U32>(num_rooms, UINT_MAX);
    U32 num_sccs = 0;
    {
        struct State {
            U32 explored_at_epoch;
            U32 min_next_explored_at_epoch; // the "lowlink" value, should also consider the node itself
            bool can_extract;
        };
        auto states = std::vector<State>(num_rooms, {UINT_MAX, UINT_MAX, false});
        U32 epoch = 0;
        auto to_extracts = std::stack<U32>();

        auto to_visits = DFS(num_rooms, nextss);
        for (U32 i = 0; i < num_rooms; i++) {
            to_visits.push(i);
            for (auto to_visit = to_visits.pop(); to_visit.id != UINT_MAX; to_visit = to_visits.pop()) {
                auto const &[curr, phase] = to_visit;

                if (phase == DFS<>::Phase::BACKTRACKING) {
                    for (auto const &next : nextss[curr]) {
                        if (!states[next].can_extract) continue;
                        states[curr].min_next_explored_at_epoch = std::min(
                            states[curr].min_next_explored_at_epoch,
                            states[next].min_next_explored_at_epoch
                        );
                    }
                    if (states[curr].min_next_explored_at_epoch == states[curr].explored_at_epoch) {
                        num_sccs++;
                        {
                            USize top;
                            do {
                                top = to_extracts.top();
                                to_extracts.pop();
                                states[top].min_next_explored_at_epoch = states[curr].min_next_explored_at_epoch;
                                states[top].can_extract = false;
                                scc_ids[top] = num_sccs - 1;
                            } while (top != curr);
                        }
                    }
                    continue;
                }
                states[curr].explored_at_epoch = states[curr].min_next_explored_at_epoch = epoch++;
                states[curr].can_extract = true;
                to_extracts.push(curr);
            }
        }

        // personal preference: invert `scc_id`s so that lower `scc_id` is equivalent to lower topological order (i.e. visited earlier)
        for (U32 i = 0; i < num_rooms; i++) {
            scc_ids[i] = num_sccs - 1 - scc_ids[i];
        }
    }

    auto scc_coin_sums = std::vector<U64>(num_sccs, 0);
    auto scc_nextss = std::vector<std::vector<U32>>(num_sccs);
    {
        for (U32 i = 0; i < num_rooms; i++) {
            scc_coin_sums[scc_ids[i]] += num_coins[i];

            for (auto const &next : nextss[i]) {
                if (scc_ids[i] != scc_ids[next]) {
                    scc_nextss[scc_ids[i]].push_back(scc_ids[next]);
                }
            }
        }
    }

    U64 max_coin_sum = 0;
    auto scc_max_coin_sums = scc_coin_sums; // max coin_sum if ending at the SCC
    {
        // update scc_max_coin_sums in topological order of the SCCs
        for (U32 i = 0; i < num_sccs; i++) {
            max_coin_sum = std::max(max_coin_sum, scc_max_coin_sums[i]);
            for (auto const &scc_next : scc_nextss[i]) {
                scc_max_coin_sums[scc_next] = std::max(scc_max_coin_sums[scc_next], scc_max_coin_sums[i] + scc_coin_sums[scc_next]);
            }
        }
    }
    std::cout << max_coin_sum << '\n';
}