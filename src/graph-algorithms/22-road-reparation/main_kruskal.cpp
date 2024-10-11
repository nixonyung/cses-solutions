#include "disjoint_set_union.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
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

// (ref.) [Minimum spanning tree - Kruskal's algorithm](https://cp-algorithms.com/graph/mst_kruskal.html)
// (ref.) [Minimum spanning tree - Kruskal with Disjoint Set Union](https://cp-algorithms.com/graph/mst_kruskal_with_dsu.html)
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    u32 num_cities;
    u32 num_roads;
    {
        std::cin >> num_cities >> num_roads;
    }

    struct Road {
        u32 start;
        u32 end;
        u32 cost;
    };
    auto roads = std::vector<Road>(num_roads);
    {
        for (u32 i = 0; i < num_roads; i++) {
            std::cin >> roads[i].start >> roads[i].end >> roads[i].cost;
            // transform to 0-indexed (personal preference)
            roads[i].start--;
            roads[i].end--;
        }
        std::ranges::stable_sort(roads, {}, [](auto const &road) { return road.cost; });
    }

    u64 min_cost_sum = 0;
    {
        auto dsu = DisjointSetUnion(num_cities);
        for (auto const &[start, end, cost] : roads) {
            if (!dsu.is_connected(start, end)) {
                dsu.connect(start, end);
                min_cost_sum += cost;
            }
        }
        if (dsu.num_roots() != 1) {
            std::cout << "IMPOSSIBLE\n";
            std::exit(0);
        }
    }
    std::cout << min_cost_sum << '\n';
}