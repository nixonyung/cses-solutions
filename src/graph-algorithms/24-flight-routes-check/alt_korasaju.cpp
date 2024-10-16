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

// (ref.) [Check if a graph is strongly connected](https://www.geeksforgeeks.org/connectivity-in-a-directed-graph/)
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
        auto to_visits = std::stack<u32>();
        auto visiteds = std::vector<bool>(num_cities, false);

        {
            to_visits.push(0);
            while (!to_visits.empty()) {
                auto const curr = to_visits.top();
                to_visits.pop();
                if (visiteds[curr]) continue;

                visiteds[curr] = true;

                for (auto const &adj : adjss[curr]) {
                    if (visiteds[adj]) continue;
                    to_visits.push(adj);
                }
            }
        }
        for (u32 i = 0; i < num_cities; i++) {
            if (!visiteds[i]) {
                std::cout << "NO\n"
                          << "1 " << i + 1 << '\n'; // "city_i cannot be visited from city_0"
                std::exit(0);
            }
            visiteds[i] = false; /// reset visiteds for next run
        }
        {
            to_visits.push(0);
            while (!to_visits.empty()) {
                auto const curr = to_visits.top();
                to_visits.pop();
                if (visiteds[curr]) continue;

                visiteds[curr] = true;

                for (auto const &adj : adj_revss[curr]) {
                    if (visiteds[adj]) continue;
                    to_visits.push(adj);
                }
            }
        }
        for (u32 i = 1; i < num_cities; i++) {
            if (!visiteds[i]) {
                std::cout << "NO\n"
                          << i + 1 << " 1\n"; // "city_i cannot reach city_0"
                std::exit(0);
            }
        }
    }
    std::cout << "YES\n";
}