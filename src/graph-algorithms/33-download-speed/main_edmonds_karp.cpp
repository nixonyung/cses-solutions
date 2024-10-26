#include "io.hpp"
#include "primitives.hpp"
#include <map>
#include <queue>
#include <vector>

// (ref.) [Maximum flow - Ford-Fulkerson and Edmonds-Karp](https://cp-algorithms.com/graph/edmonds_karp.html)
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
        struct ToVisit {
            U32 computer_id;
            U64 curr_flow;
            U32 prev_computer_id;
        };
        auto to_visits = std::priority_queue<
            ToVisit,
            std::vector<ToVisit>,
            decltype(BINARY_FN(lhs, rhs) { return lhs.curr_flow < rhs.curr_flow; })>(); // prioritize higher flow, does not guarantee returning the highest possible flow but tries to maximize it
        auto prevs = std::vector<U32>(num_computers);

        bool has_update = true;
        while (has_update) {
            has_update = false;
            while (!to_visits.empty()) to_visits.pop();
            prevs.assign(num_computers, UINT_MAX);

            to_visits.push({0, ULONG_MAX, UINT_MAX});
            while (!to_visits.empty()) {
                auto const [curr, curr_flow, prev] = to_visits.top();
                to_visits.pop();
                if (prevs[curr] != UINT_MAX) continue;
                prevs[curr] = prev;

                if (curr == num_computers - 1) {
                    max_flow += curr_flow;
                    {
                        U32 curr = num_computers - 1;
                        while (curr != 0) {
                            auto const &prev = prevs[curr];
                            capacityss[prev][curr] -= curr_flow;
                            capacityss[curr][prev] += curr_flow;
                            curr = prev;
                        }
                    }
                    has_update = true;
                    break;
                }

                for (auto const &[next, capacity] : capacityss[curr]) {
                    if (prevs[next] != UINT_MAX || capacity == 0) continue;
                    to_visits.push({next, std::min(curr_flow, capacity), curr});
                }
            }
        }
    }
    std::cout << max_flow << '\n';
}