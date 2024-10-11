#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <queue>
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

// (ref.) [Minimum spanning tree - Prim's algorithm](https://cp-algorithms.com/graph/mst_prim.html)
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    u32 num_cities;
    u32 num_roads;
    {
        std::cin >> num_cities >> num_roads;
    }

    struct Adj {
        u32 end;
        u32 cost;
    };
    auto adjss = std::vector<std::vector<Adj>>(num_cities);
    {
        u32 start;
        u32 end;
        u32 cost;
        for (u32 i = 0; i < num_roads; i++) {
            std::cin >> start >> end >> cost;
            // transform to 0-indexed (personal preference)
            start--;
            end--;

            adjss[start].push_back({end, cost});
            adjss[end].push_back({start, cost});
        }
    }

    u64 min_cost_sum = 0;
    {
        struct ToVisit {
            u32 city_id;
            u32 cost;
        };
        auto to_visits = std::priority_queue<
            ToVisit,
            std::vector<ToVisit>,
            decltype([](auto const &lhs, auto const &rhs) { return lhs.cost > rhs.cost; })>();
        auto visiteds = std::vector<bool>(num_cities, false);
        u32 num_visiteds = 0;

        to_visits.push({0, 0});
        while (!to_visits.empty()) {
            auto const [curr, cost] = to_visits.top();
            to_visits.pop();
            if (visiteds[curr]) continue;

            min_cost_sum += cost;
            visiteds[curr] = true;
            num_visiteds++;
            if (num_visiteds == num_cities) {
                std::cout << min_cost_sum << '\n';
                break;
            }

            for (auto const &[adj, cost] : adjss[curr]) {
                if (visiteds[adj]) continue;
                to_visits.push({adj, cost});
            }
        }
        if (num_visiteds != num_cities) {
            std::cout << "IMPOSSIBLE\n";
        }
    }
}