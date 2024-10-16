#include <climits>
#include <cstdint>
#include <cstdlib>
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

// (ref.) [Tarjan's Strongly Connected Component (SCC) Algorithm (UPDATED) | Graph Theory](https://youtu.be/wUgWX0nc4NY?si=a9VpzlmTYt1gZDPs)
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    u32 num_cities;
    u32 num_flights;
    {
        std::cin >> num_cities >> num_flights;
    }

    auto adjss = std::vector<std::vector<u32>>(num_cities);
    {
        u32 start;
        u32 end;
        for (u32 i = 0; i < num_flights; i++) {
            std::cin >> start >> end;
            // transform to 0-indexed (personal preference)
            start--;
            end--;

            adjss[start].push_back(end);
        }
    }

    enum class Phase : unsigned char {
        EXPLORE,
        BACKTRACKING,
        DONE,
    };
    struct State {
        Phase phase;
        u32 visited_at_epoch;
        u32 lowlink; // the lowest `visited_at_epoch` this city can reach, including itself
        bool can_extract;
    };
    auto states = std::vector<State>(num_cities, {Phase::EXPLORE, UINT_MAX, UINT_MAX, false});
    {
        auto to_visits = std::stack<u32>();
        auto can_extracts = std::stack<u32>();

        u32 epoch = 0;
        to_visits.push(0);
        while (!to_visits.empty()) {
            auto const curr = to_visits.top();
            to_visits.pop();

            switch (states[curr].phase) {
            case Phase::DONE: {
                continue;
            } break;
            case Phase::EXPLORE: {
                states[curr].phase = Phase::BACKTRACKING;
                states[curr].visited_at_epoch = states[curr].lowlink = epoch++;
                states[curr].can_extract = true;
                can_extracts.push(curr);

                to_visits.push(curr);
                for (auto const &adj : adjss[curr]) {
                    if (states[adj].phase != Phase::EXPLORE) continue;
                    to_visits.push(adj);
                }
            } break;
            case Phase::BACKTRACKING: {
                states[curr].phase = Phase::DONE;

                for (auto const &adj : adjss[curr]) {
                    if (!states[adj].can_extract) continue;
                    states[curr].lowlink = std::min(states[curr].lowlink, states[adj].lowlink);
                }
                if (states[curr].lowlink == states[curr].visited_at_epoch) {
                    while (can_extracts.top() != curr) {
                        states[can_extracts.top()].lowlink = states[curr].lowlink;
                        states[can_extracts.top()].can_extract = false;
                        can_extracts.pop();
                    }
                    states[can_extracts.top()].can_extract = false;
                    can_extracts.pop();
                }
            } break;
            }
        }
    }
    for (u32 i = 0; i < num_cities; i++) {
        if (states[i].phase == Phase::EXPLORE) {
            std::cout << "NO\n"
                      << "1 " << i + 1 << '\n'; // "city_i cannot be visited from city_0"
            std::exit(0);
        }
        if (states[i].lowlink != 0) {
            std::cout << "NO\n"
                      << i + 1 << " 1\n"; // "city_i cannot reach city_0"
            std::exit(0);
        }
    }
    std::cout << "YES\n";
}