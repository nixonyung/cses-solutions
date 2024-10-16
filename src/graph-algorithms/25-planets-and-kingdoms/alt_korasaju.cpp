#include <climits>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <ranges>
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

// (ref.) [Kosaraju's algorithm](https://www.wikiwand.com/en/articles/Kosaraju%27s_algorithm)
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    u32 num_planets;
    u32 num_routes;
    {
        std::cin >> num_planets >> num_routes;
    }

    auto adjss = std::vector<std::vector<u32>>(num_planets);
    auto adj_revss = std::vector<std::vector<u32>>(num_planets);
    {
        u32 start;
        u32 end;
        for (u32 i = 0; i < num_routes; i++) {
            std::cin >> start >> end;
            // transform to 0-indexed (personal preference)
            start--;
            end--;

            adjss[start].push_back(end);
            adj_revss[end].push_back(start);
        }
    }

    auto kingdom_ids = std::vector<u32>(num_planets, UINT_MAX);
    u32 num_kingdoms = 0;
    {
        auto planets_ordered = std::stack<u32>();
        auto to_visits = std::stack<u32>(); // preallocate memory
        {
            enum class Phase : unsigned char {
                EXPLORE,
                BACKTRACKING,
                DONE,
            };
            auto phases = std::vector<Phase>(num_planets, Phase::EXPLORE);
            for (u32 i = 0; i < num_planets; i++) {
                if (phases[i] != Phase::EXPLORE) continue;
                to_visits.push(i);
                while (!to_visits.empty()) {
                    auto const curr = to_visits.top();
                    to_visits.pop();

                    switch (phases[curr]) {
                    case Phase::DONE: {
                        continue;
                    } break;
                    case Phase::EXPLORE: {
                        phases[curr] = Phase::BACKTRACKING;

                        to_visits.push(curr);
                        for (auto const &adj : adjss[curr] | std::views::reverse) { // reverse adjs to match test outputs
                            if (phases[adj] != Phase::EXPLORE) continue;
                            to_visits.push(adj);
                        }
                    } break;
                    case Phase::BACKTRACKING: {
                        phases[curr] = Phase::DONE;
                        planets_ordered.push(curr);
                    } break;
                    }
                }
            }
        }
        {
            while (!planets_ordered.empty()) {
                auto const i = planets_ordered.top();
                planets_ordered.pop();
                if (kingdom_ids[i] != UINT_MAX) continue;

                num_kingdoms++;
                to_visits.push(i);
                while (!to_visits.empty()) {
                    auto const curr = to_visits.top();
                    to_visits.pop();
                    if (kingdom_ids[curr] != UINT_MAX) continue;

                    kingdom_ids[curr] = num_kingdoms;

                    for (auto const &adj : adj_revss[curr]) {
                        if (kingdom_ids[adj] != UINT_MAX) continue;
                        to_visits.push(adj);
                    }
                }
            }
        }
    }
    std::cout << num_kingdoms << '\n';
    for (auto const &kingdom_id : kingdom_ids) {
        std::cout << kingdom_id << ' ';
    }
    std::cout << '\n';
}