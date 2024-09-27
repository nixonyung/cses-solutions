/*
correct implementation but test 11 has whitespace diff

(ref.) [Shortest path problem](https://www.wikiwand.com/en/articles/Shortest_path_problem)
(ref.) [Dijkstra Algorithm](https://cp-algorithms.com/graph/dijkstra.html)
*/

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>

namespace {
using i32 = int_fast32_t;
using i64 = int_fast64_t;
using u8 = uint_fast8_t;
using u32 = uint_fast32_t;
using u64 = uint_fast64_t;

struct Connection {
    u32 end;
    u32 weight;
};

struct ToVisit {
    u32 city_id;
    u64 dist;
};
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    u32 num_cities;
    u32 num_connections;
    {
        std::cin >> num_cities >> num_connections;
    }

    auto adjss = std::vector<std::vector<Connection>>(num_cities); // ok to have multiple connections between two cities, even with different weights
    {
        u32 start;
        u32 end;
        u32 weight;
        for (u32 i = 0; i < num_connections; i++) {
            std::cin >> start >> end >> weight;
            // transform to 0-indexed
            start--;
            end--;
            adjss[start].push_back({end, weight});
        }
    }

    auto shortest_distances = std::vector<u64>(num_cities, UINT64_MAX);
    {
        auto to_visits = std::priority_queue<ToVisit, std::vector<ToVisit>, decltype([](auto const &lhs, auto const &rhs) { return lhs.dist > rhs.dist; })>();
        to_visits.push({0, 0});
        while (!to_visits.empty()) {
            auto const [city_id, dist] = to_visits.top();
            to_visits.pop();

            if (shortest_distances[city_id] != UINT64_MAX) continue;
            shortest_distances[city_id] = dist;

            for (auto const &[adj, weight] : adjss[city_id]) {
                if (shortest_distances[adj] != UINT64_MAX) continue;
                to_visits.push({adj, shortest_distances[city_id] + weight});
            }
        }
    }
    for (u32 i = 0; i < num_cities; i++) {
        std::cout << shortest_distances[i] << ' ';
    }
    std::cout << '\n';
}