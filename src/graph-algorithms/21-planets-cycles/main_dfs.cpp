#include <climits>
#include <cstdint>
#include <iostream>
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

// idea: in a "functional graph" (i.e. each node has exactly 1 out-edge), every node "points to" exactly 1 cycle
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    u32 num_planets;
    {
        std::cin >> num_planets;
    }

    auto nexts = std::vector<u32>(num_planets);
    {
        for (u32 j = 0; j < num_planets; j++) {
            std::cin >> nexts[j];
            nexts[j]--; // transform to 0-indexed (personal preference)
        }
    }

    struct State {
        u32 cycle_id; // which cycle the node "points to"
        u32 dist_to_cycle;
    };
    auto states = std::vector<State>(num_planets, {UINT_MAX, UINT_MAX});
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

                auto const &adj = nexts[curr];
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
                                    0,
                                };
                                cycle_len++;
                                planet_phases[_curr] = Phase::DONE;
                                _curr = nexts[_curr];
                            } while (_curr != adj);
                        }
                        cycle_lens.push_back(cycle_len);
                    } break;
                    }
                } break;
                case Phase::BACKTRACK: {
                    states[curr] = {
                        states[adj].cycle_id,
                        states[adj].dist_to_cycle + 1
                    };
                    planet_phases[curr] = Phase::DONE;
                } break;
                }
            }
        }
    }
    for (u32 i = 0; i < num_planets; i++) {
        std::cout << states[i].dist_to_cycle + cycle_lens[states[i].cycle_id] << ' ';
    }
    std::cout << '\n';
}