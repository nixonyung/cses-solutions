#include "io.hpp"
#include "primitives.hpp"
#include <map>
#include <ranges>
#include <stack>
#include <vector>

// (ref.) [Maximum flow - Ford-Fulkerson and Edmonds-Karp](https://cp-algorithms.com/graph/edmonds_karp.html)
// (ref.) [Max-flow min-cut theorem](https://cp-algorithms.com/graph/edmonds_karp.html#max-flow-min-cut-theorem)
// correct implementation but outputs are different from tests
int main() {
    enable_fast_io();

    auto num_citys = read<U32>();
    auto num_streets = read<U32>();
    auto capacityss = std::vector<std::map<U32, U8>>(num_citys);
    {
        for (U32 i = 0; i < num_streets; i++) {
            // peronsal preference: transform to 0-indexed
            auto start = read<U32>() - 1;
            auto end = read<U32>() - 1;
            /*
            for undirected graphs, still need to use int (instead of bool) to represent capacity in order to represent the following states:
            - capacityss[prev][curr] == 1 && capacityss[curr][prev] == 1: both (prev, curr) and (curr, prev) are available
            - capacityss[prev][curr] == 0 && capacityss[curr][prev] == 2: (prev, curr) is taken, the reverse edge (curr, prev) is available
            - capacityss[prev][curr] == 2 && capacityss[curr][prev] == 0: (curr, prev) is taken, the reverse edge (prev, curr) is available
            */
            capacityss[start][end] = 1;
            capacityss[end][start] = 1;
        }
    }

    U64 max_flow = 0;
    {
        struct ToVisit {
            U32 path_len;
            U32 city_id;
        };
        auto to_visits = std::stack<ToVisit>();
        auto visiteds = std::vector<bool>(num_citys, false);
        auto path = std::vector<U32>();

        bool has_update = true;
        while (has_update) {
            has_update = false;
            while (!to_visits.empty()) to_visits.pop();
            visiteds.resize(visiteds.size(), false);

            to_visits.push({0, 0});
            while (!to_visits.empty()) {
                auto const [path_len, curr] = to_visits.top();
                to_visits.pop();
                // no need to assign visiteds[path.top()] = false because revisiting an exhausted city will not find a new path to city_n
                path.resize(path_len);
                path.push_back(curr);
                visiteds[curr] = true;

                for (auto const &[next, capacity] : capacityss[curr]) {
                    if (visiteds[next] || capacity == 0) continue;
                    if (next == num_citys - 1) {
                        max_flow += 1;
                        for (U32 curr = num_citys - 1; auto const &prev : path | std::views::reverse) {
                            capacityss[prev][curr] -= 1;
                            capacityss[curr][prev] += 1;
                            curr = prev;
                        }
                        has_update = true;
                        goto NEW_FLOW_FOUND;
                    }
                    to_visits.push({path_len + 1, next});
                }
            }
        NEW_FLOW_FOUND:;
        }
    }
    std::cout << max_flow << '\n';

    // find the min-cut
    auto visiteds = std::vector<bool>(num_citys, false);
    {
        auto to_visits = std::stack<U32>();
        to_visits.push(0);
        while (!to_visits.empty()) {
            auto const curr = to_visits.top();
            to_visits.pop();
            if (visiteds[curr]) continue;
            visiteds[curr] = true;

            for (auto const &[next, is_available] : capacityss[curr]) {
                if (visiteds[next] || !is_available) continue;
                to_visits.push(next);
            }
        }
    }
    for (U32 i = 0; i < num_citys; i++) {
        if (!visiteds[i]) continue;
        for (auto const &[next, is_available] : capacityss[i]) {
            if (!visiteds[next] && !is_available) {
                std::cout << i + 1 << ' ' << next + 1 << '\n';
            }
        }
    }
}