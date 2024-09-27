/*
(ref.) [Shortest path problem](https://www.wikiwand.com/en/articles/Shortest_path_problem)
(ref.) [Floyd-Warshall Algorithm](https://cp-algorithms.com/graph/all-pair-shortest-path-floyd-warshall.html)
*/

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace {
using i32 = int_fast32_t;
using i64 = int_fast64_t;
using u8 = uint_fast8_t;
using u32 = uint_fast32_t;
using u64 = uint_fast64_t;
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    u32 num_cities;
    u32 num_connections;
    u32 num_queries;
    {
        std::cin >> num_cities >> num_connections >> num_queries;
    }

    auto shortest_distancess = std::vector<std::vector<u64>>(num_cities + 1, std::vector<u64>(num_cities + 1, UINT64_MAX));
    {
        {
            u32 start;
            u32 end;
            u32 weight;
            for (u32 i = 0; i < num_connections; i++) {
                std::cin >> start >> end >> weight;
                shortest_distancess[start][end] = std::min(shortest_distancess[start][end], (u64)weight);
                shortest_distancess[end][start] = std::min(shortest_distancess[end][start], (u64)weight);
            }
        }
        for (u32 i = 1; i <= num_cities; i++) {
            shortest_distancess[i][i] = 0;
        }
        for (u32 k = 1; k <= num_cities; k++) {
            for (u32 i = 1; i <= num_cities; i++) {
                for (u32 j = 1; j <= num_cities; j++) {
                    if (shortest_distancess[i][k] == UINT64_MAX || shortest_distancess[k][j] == UINT64_MAX) continue;
                    shortest_distancess[i][j] = std::min(
                        shortest_distancess[i][j],
                        shortest_distancess[i][k] + shortest_distancess[k][j]
                    );
                }
            }
        }
    }
    {
        u32 start;
        u32 end;
        while (num_queries--) {
            std::cin >> start >> end;
            if (shortest_distancess[start][end] != UINT64_MAX) {
                std::cout << shortest_distancess[start][end] << '\n';
            } else {
                std::cout << -1 << '\n';
            }
        }
    }
}