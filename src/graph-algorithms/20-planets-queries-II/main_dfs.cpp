#include <bit>
#include <climits>
#include <cstdint>
#include <iostream>
#include <limits>
#include <stack>
#include <vector>

namespace {
// non-standard data types
using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;
using i8 = int8_t;
using i32 = int32_t;
using i64 = int64_t;
using usize = std::size_t;
using isize = std::make_signed_t<std::size_t>;
} // namespace

// (ref.) [CSES - Planets Queries II](https://usaco.guide/problems/cses-1160-planets-queries-ii/solution
// idea: in a "functional graph" (i.e. each node has exactly 1 out-edge), every node "points to" exactly 1 cycle
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const u32 MAX_CYCLE_LEN = 2e5;
    const u32 MAX_DEPTH = std::numeric_limits<decltype(MAX_CYCLE_LEN)>::digits - 1 - std::countl_zero(MAX_CYCLE_LEN); // `2 ^ MAX_DEPTH` is the largest power of 2 not greater than MAX_K

    u32 num_planets;
    u32 num_queries;
    {
        std::cin >> num_planets >> num_queries;
    }

    auto nextss = std::vector<u32>((MAX_DEPTH + 1) * num_planets); // nextss[i * num_planets + j] is the `2^i`-th next element of `j`
    {
        {
            for (u32 j = 0; j < num_planets; j++) {
                std::cin >> nextss[j];
                nextss[j]--; // transform to 0-indexed (personal preference)
            }
        }
        for (u32 i = 1; i <= MAX_DEPTH; i++) {
            for (u32 j = 0; j < num_planets; j++) {
                nextss[i * num_planets + j] = nextss[(i - 1) * num_planets + nextss[(i - 1) * num_planets + j]];
            }
        }
    }

    struct State {
        u32 cycle_id; // which cycle the node "points to"
        u32 node_id;  // id of this node in the cycle, note that it should be propagated to nodes "pointing to" this node in the cycle
        u32 dist_to_cycle;
    };
    auto states = std::vector<State>(num_planets, {UINT_MAX, UINT_MAX, UINT_MAX});
    auto cycle_lens = std::vector<u32>();
    {
        // "3-colors DFS"
        enum class Phase : unsigned char {
            EXPLORE,
            BACKTRACK,
            DONE,
        };
        auto planet_phases = std::vector<Phase>(num_planets, Phase::EXPLORE);

        struct ToVisit {
            u32 planet_id;
            u32 visit_at;
        };
        auto to_visits = std::stack<ToVisit>();

        auto visit_ats = std::vector<u32>(num_planets, UINT_MAX);

        for (u32 i = 0; i < num_planets; i++) {
            to_visits.push({i, 0});
            while (!to_visits.empty()) {
                auto const [curr, visit_at] = to_visits.top();
                to_visits.pop();

                auto const &adj = nextss[curr];
                switch (planet_phases[curr]) {
                case Phase::DONE:
                    break;
                case Phase::EXPLORE: {
                    visit_ats[curr] = visit_at;
                    planet_phases[curr] = Phase::BACKTRACK; // need to update phanet_phases[curr] here to detect 1-node cycles

                    switch (planet_phases[adj]) {
                    case Phase::DONE: {
                        states[curr] = {
                            states[adj].cycle_id,
                            states[adj].node_id, // propagate `node_id` to nodes "pointing to" the node in the cycle
                            states[adj].dist_to_cycle + 1
                        };
                        planet_phases[curr] = Phase::DONE;
                    } break;
                    case Phase::EXPLORE: {
                        to_visits.push({curr, visit_at}); // revisit curr AFTER visiting adj
                        to_visits.push({adj, visit_at + 1});
                    } break;
                    case Phase::BACKTRACK: {
                        // found cycle
                        u32 cycle_len = 0;
                        {
                            u32 _curr = adj;
                            do {
                                states[_curr] = {
                                    (u32)cycle_lens.size(),
                                    cycle_len++,
                                    0,
                                };
                                planet_phases[_curr] = Phase::DONE;
                                _curr = nextss[_curr];
                            } while (_curr != adj);
                        }
                        cycle_lens.push_back(cycle_len);
                    } break;
                    }
                } break;
                case Phase::BACKTRACK: {
                    states[curr] = {
                        states[adj].cycle_id,
                        states[adj].node_id, // propagate `node_id` to nodes "pointing to" the node in the cycle
                        states[adj].dist_to_cycle + 1
                    };
                    planet_phases[curr] = Phase::DONE;
                } break;
                }
            }
        }
    }

    {
        u32 start;
        u32 end;
        while (num_queries--) {
            std::cin >> start >> end;
            // transform to 0-indexed (personal preference)
            start--;
            end--;

            if (
                states[start].cycle_id != states[end].cycle_id ||
                states[start].dist_to_cycle < states[end].dist_to_cycle
            ) {
                std::cout << "-1\n";
                continue;
            }
            // if `end` is not in the cycle, need to check if `start` can reach `end`
            if (states[end].dist_to_cycle != 0) {
                u32 dist = states[start].dist_to_cycle - states[end].dist_to_cycle;

                u32 curr = start;
                for (u32 i = 0; i <= MAX_DEPTH; i++) {
                    if (dist & (1 << i)) {
                        curr = nextss[i * num_planets + curr];
                    }
                }
                if (curr != end) {
                    std::cout << "-1\n";
                } else {
                    std::cout << dist << '\n';
                }
            }
            // else `start` can always traverse the cycle and find `end`
            else {
                auto const &cycle_len = cycle_lens[states[start].cycle_id];
                u32 dist = (states[start].dist_to_cycle - states[end].dist_to_cycle) +
                           (states[end].node_id + cycle_len - states[start].node_id) % cycle_len;
                std::cout << dist << '\n';
            }
        }
    }
}