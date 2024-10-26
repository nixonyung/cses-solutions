#include "io.hpp"
#include "primitives.hpp"
#include <map>
#include <stack>
#include <vector>

// (ref.) [Maximum flow - Ford-Fulkerson and Edmonds-Karp](https://cp-algorithms.com/graph/edmonds_karp.html)
// (ref.) [Maximum Bipartite Matching](https://www.geeksforgeeks.org/maximum-bipartite-matching/)
// correct implementation but outputs are different from tests
int main() {
    enable_fast_io();

    auto num_boys = read<U32>();
    auto num_girls = read<U32>();
    auto num_preferences = read<U32>();
    const U32 NUM_NODES = 1 + num_boys + num_girls + 1;            // imaginary source + boys + girls + imaginary sink
    auto capacityss = std::vector<std::map<U32, bool>>(NUM_NODES); // can use bool if there is at most 1 directed edge between any two nodes
    {
        for (U32 i = 0; i < num_boys; i++) {
            capacityss[0][1 + i] = true;
            capacityss[1 + i][0] = false;
        }
        for (U32 i = 0; i < num_girls; i++) {
            capacityss[1 + num_boys + i][NUM_NODES - 1] = true;
            capacityss[NUM_NODES - 1][1 + num_boys + i] = false;
        }
        for (U32 i = 0; i < num_preferences; i++) {
            // peronsal preference: transform to 0-indexed
            auto boy_id = read<U32>() - 1;
            auto girl_id = read<U32>() - 1;
            capacityss[1 + boy_id][1 + num_boys + girl_id] = true;
            capacityss[1 + num_boys + girl_id][1 + boy_id] = false;
        }
    }

    U64 max_flow = 0;
    auto boy_to_girl = std::vector<U32>(num_boys, UINT_MAX);
    {
        auto to_visits = std::stack<U32>();
        auto prevs = std::vector<U32>(NUM_NODES);

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
                    if (next == NUM_NODES - 1) {
                        max_flow += 1;
                        for (U32 curr = NUM_NODES - 1; curr != 0; curr = prevs[curr]) {
                            auto const &prev = prevs[curr];
                            if (prev >= 1 && prev < 1 + num_boys) {
                                boy_to_girl[prev - 1] = curr - 1 - num_boys;
                            }
                            capacityss[prev][curr] = false;
                            capacityss[curr][prev] = true;
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
    for (U32 i = 0; i < num_boys; i++) {
        if (boy_to_girl[i] != UINT_MAX) {
            std::cout << i + 1 << ' ' << boy_to_girl[i] + 1 << '\n';
        }
    }
}