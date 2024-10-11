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
    auto adj_revss = std::vector<std::vector<u32>>(num_cities);
    {
        u32 start;
        u32 end;
        for (u32 i = 0; i < num_flights; i++) {
            std::cin >> start >> end;
            // transform to 0-indexed (personal preference)
            start--;
            end--;

            adjss[start].push_back(end);
            adj_revss[end].push_back(start);
        }
    }

    {
        enum class Phase : unsigned char {
            EXPLORE,
            BACKTRACKING,
            DONE,
        };
        struct State {
            Phase phase;
            u32 visited_at;
            u32 lowlink;
            bool in_to_extract;
        };
        auto states = std::vector<State>(num_cities, {Phase::EXPLORE, UINT_MAX, UINT_MAX, false});

        auto to_visits = std::stack<u32>();
        auto to_extract = std::stack<u32>();

        to_visits.push(0);
        u32 epoch = 0;
        while (!to_visits.empty()) {
            auto const curr = to_visits.top();
            to_visits.pop();

            switch (states[curr].phase) {
            case Phase::DONE: {
                continue;
            } break;
            case Phase::EXPLORE: {
                states[curr] = {
                    Phase::BACKTRACKING,
                    epoch,
                    epoch,
                    true
                };
                epoch++;
                to_extract.push(curr);

                to_visits.push(curr);
                for (auto const &adj : adjss[curr]) {
                    if (states[adj].phase != Phase::EXPLORE) continue;
                    to_visits.push(adj);
                }
            } break;
            case Phase::BACKTRACKING: {
                states[curr].phase = Phase::DONE;

                // std::cout << curr << ": ";
                for (auto const &adj : adjss[curr]) {
                    if (!states[adj].in_to_extract) continue;
                    states[curr].lowlink = std::min(states[curr].lowlink, states[adj].lowlink);
                    // std::cout << adj << "(" << states[adj].visited_at << ',' << states[adj].lowlink << ") ";
                }
                if (states[curr].lowlink == states[curr].visited_at) {
                    while (to_extract.top() != curr) {
                        states[to_extract.top()].lowlink = states[curr].lowlink;
                        states[to_extract.top()].in_to_extract = false;
                        to_extract.pop();
                    }
                    states[to_extract.top()].in_to_extract = false;
                    to_extract.pop();
                }
                // std::cout << "=> " << states[curr].lowlink << '\n';
            } break;
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
    }
    std::cout << "YES\n";
}