#include "io.hpp"
#include "primitives.hpp"
#include <map>
#include <ranges>
#include <stack>
#include <vector>

// (ref.) [Maximum flow - Ford-Fulkerson and Edmonds-Karp](https://cp-algorithms.com/graph/edmonds_karp.html)
// correct implementation but outputs are different from tests
int main() {
    enable_fast_io();

    auto num_rooms = read<U32>();
    auto num_teleporters = read<U32>();
    auto capacityss = std::vector<std::map<U32, U8>>(num_rooms);
    {
        for (U32 i = 0; i < num_teleporters; i++) {
            // peronsal preference: transform to 0-indexed
            auto start = read<U32>() - 1;
            auto end = read<U32>() - 1;
            capacityss[start][end] += 1;
            capacityss[end][start] += 0; // ensure reverse edge exists
        }
    }

    U64 max_flow = 0;
    auto flowss = std::vector<std::map<U32, I8>>(num_rooms);
    {
        auto to_visits = std::stack<U32>();
        auto prevs = std::vector<U32>(num_rooms);

        bool has_update = true;
        while (has_update) {
            has_update = false;
            while (!to_visits.empty()) to_visits.pop();
            prevs.assign(prevs.size(), UINT_MAX);

            to_visits.push(0);
            while (!to_visits.empty()) {
                auto const curr = to_visits.top();
                to_visits.pop();

                for (auto const &[next, capacity] : capacityss[curr]) {
                    if (prevs[next] != UINT_MAX || !capacity) continue;
                    prevs[next] = curr;
                    if (next == num_rooms - 1) {
                        max_flow += 1;
                        for (U32 curr = num_rooms - 1; curr != 0; curr = prevs[curr]) {
                            auto const &prev = prevs[curr];
                            flowss[prev][curr]++;
                            flowss[curr][prev]--;
                            capacityss[prev][curr]--;
                            capacityss[curr][prev]++;
                        }
                        has_update = true;
                        goto UPDATE_END;
                    }
                    to_visits.push(next);
                }
            }
        UPDATE_END:;
        }
    }
    std::cout << max_flow << '\n';
    {
        struct ToVisit {
            U32 path_len;
            U32 room_id;
        };
        auto to_visits = std::stack<ToVisit>();
        auto path = std::vector<U32>();
        auto visiteds = std::vector<bool>(num_rooms, false);

        for (U32 i = 0; i < max_flow; i++) {
            while (!to_visits.empty()) to_visits.pop();
            path.clear();
            visiteds.assign(visiteds.size(), false);

            to_visits.push({0, 0});
            while (!to_visits.empty()) {
                auto const [path_len, curr] = to_visits.top();
                to_visits.pop();
                path.resize(path_len);
                path.push_back(curr);

                for (auto const &[next, flow] : flowss[curr]) {
                    if (visiteds[next] || flow <= 0) continue; // flow < 0 should be ignored
                    visiteds[next] = true;
                    if (next == num_rooms - 1) {
                        std::cout << path.size() + 1 << '\n';
                        for (auto const &room : path) {
                            std::cout << room + 1 << ' ';
                        }
                        std::cout << next + 1 << ' ' << '\n';

                        U32 curr = next;
                        for (auto const &prev : path | std::views::reverse) {
                            flowss[prev][curr]--;
                            curr = prev;
                        }
                        goto UPDATE_END2;
                    }
                    to_visits.push({path_len + 1, next});
                }
            UPDATE_END2:;
            }
        }
    }
}