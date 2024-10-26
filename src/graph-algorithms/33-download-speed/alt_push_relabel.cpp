#include "io.hpp"
#include "primitives.hpp"
#include <map>
#include <queue>
#include <vector>

// (ref.) [Maximum flow - Ford-Fulkerson and Edmonds-Karp](https://cp-algorithms.com/graph/edmonds_karp.html)
// (ref.) [Maximum flow - Push-relabel method improved](https://cp-algorithms.com/graph/push-relabel-faster.html)
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

    struct State {
        U32 height;
        U64 excess;
    };
    auto states = std::vector<State>(num_computers, {0, 0});
    {
        states[0].height = num_computers;
        for (auto const &[next, capacity] : capacityss[0]) {
            states[0].excess += capacity;
        }

        struct ToVisit {
            U32 computer_id;
            U32 height;
        };
        auto to_visits = std::priority_queue<
            ToVisit,
            std::vector<ToVisit>,
            decltype(BINARY_FN(lhs, rhs) { return lhs.height < rhs.height; })>();
        to_visits.push({0, states[0].height});
        while (!to_visits.empty()) {
            auto const [curr, _] = to_visits.top();
            to_visits.pop();

            while (states[curr].excess != 0) {
                // TODO: can refine when to relabel?
                if (curr != 0) {
                    U32 min_pushable_next_height = UINT_MAX;
                    for (auto const &[next, capacity] : capacityss[curr]) {
                        if (capacity == 0) continue;
                        min_pushable_next_height = std::min(min_pushable_next_height, states[next].height);
                    }
                    states[curr].height = min_pushable_next_height + 1;
                }

                for (auto const &[next, capacity] : capacityss[curr]) {
                    if (curr != 0 && states[curr].height != states[next].height + 1) continue;
                    auto const flow = std::min(states[curr].excess, capacity);
                    if (flow == 0) continue;
                    capacityss[curr][next] -= flow;
                    capacityss[next][curr] += flow;
                    states[next].excess += flow;
                    states[curr].excess -= flow;
                    if (
                        next != 0 &&              // flow back to source means the flow graph cannot handle the excess flow
                        next != num_computers - 1 // flow to sink directly contributes to the max flow, no need to discharge
                    ) to_visits.push({next, states[next].height});
                    if (states[curr].excess == 0) break;
                }
            }
        }
    }
    std::cout << states[num_computers - 1].excess << '\n';
}