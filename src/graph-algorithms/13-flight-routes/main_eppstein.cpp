// (ref.) [[Tutorial] k shortest paths and Eppstein's algorithm](https://codeforces.com/blog/entry/102085)
// (ref.) [Finding the k Shortest Paths](https://ics.uci.edu/~eppstein/pubs/Epp-SJC-98.pdf)

#include <bitset>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>

// custom primitive data types
typedef unsigned int uint;
typedef unsigned long ulong;
typedef std::size_t usize;
typedef std::make_signed_t<std::size_t> isize;

namespace {
struct Route {
    uint id;
    uint end;
    uint price;
};
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const uint MAX_NUM_CITIES = 1e5;
    const uint MAX_NUM_ROUTES = 2e5;

    uint num_cities;
    uint num_routes;
    uint k;
    {
        std::cin >> num_cities >> num_routes >> k;
    }

    auto adjss = std::vector<std::vector<Route>>(num_cities);
    auto adj_revss = std::vector<std::vector<Route>>(num_cities);
    {
        uint start;
        uint end;
        uint price;
        for (uint i = 0; i < num_routes; i++) {
            std::cin >> start >> end >> price;
            // transform to 0-indexed (personal preference)
            start--;
            end--;

            adjss[start].push_back({i, end, price});
            adj_revss[end].push_back({i, start, price});
        }
    }

    // Dijkstra from `end`
    auto min_price_sums = std::vector<ulong>(num_cities, ULONG_MAX);
    auto parents = std::vector<uint>(num_cities, UINT_MAX);
    auto mst = std::bitset<MAX_NUM_ROUTES>(); // mst[route_id] = true iff route_id is in the minimum spanning tree
    {
        struct Path {
            uint ending_route_id;
            uint end_city_id;
            ulong price_sum;
            uint parent;
        };
        auto to_visits = std::priority_queue<
            Path,
            std::vector<Path>,
            decltype([](auto const &lhs, auto const &rhs) { return lhs.price_sum > rhs.price_sum; })>();

        to_visits.push({UINT_MAX, num_cities - 1, 0, UINT_MAX});
        while (!to_visits.empty()) {
            auto const [ending_route_id, curr, price_sum, parent] = to_visits.top();
            to_visits.pop();
            if (min_price_sums[curr] != ULONG_MAX) continue;

            min_price_sums[curr] = price_sum;
            parents[curr] = parent;
            if (ending_route_id != UINT_MAX) mst[ending_route_id] = true;

            for (auto const &[route_id, adj, price] : adj_revss[curr]) {
                if (min_price_sums[adj] != ULONG_MAX) continue;
                to_visits.push({route_id, adj, price_sum + price, curr});
            }
        }
    }

    // idea: use linked list so that `curr` can "see" the current AND future sidetracks (along its shortest path to `end`)
    struct Sidetrack {
        ulong delta;
        uint end;
        usize next_sidetrack_id; // imitating linked list
    };
    auto sidetracks = std::vector<Sidetrack>();
    auto city_last_sidetrack_ids = std::vector<usize>(num_cities, ULONG_MAX);
    {
        // use BFS to level-traverse the MST
        auto to_visits = std::queue<uint>();
        auto visiteds = std::bitset<MAX_NUM_CITIES>();
        to_visits.push(num_cities - 1);
        while (!to_visits.empty()) {
            auto const curr = to_visits.front();
            to_visits.pop();

            if (curr != num_cities - 1) city_last_sidetrack_ids[curr] = city_last_sidetrack_ids[parents[curr]];
            for (auto const &[route_id, adj, price] : adjss[curr]) {
                if (mst[route_id]) continue;
                sidetracks.push_back(
                    {price + min_price_sums[adj] - min_price_sums[curr],
                     adj,
                     city_last_sidetrack_ids[curr]}
                );
                city_last_sidetrack_ids[curr] = sidetracks.size() - 1;
            }

            for (auto const &[route_id, adj, price] : adj_revss[curr]) {
                if (!mst[route_id] || visiteds[adj]) continue;
                to_visits.push(adj);
                visiteds[adj] = true;
            }
        }
    }

    {
        struct Delta {
            uint end_city_id;
            ulong delta_sum;
        };
        auto to_visits = std::priority_queue<
            Delta,
            std::vector<Delta>,
            decltype([](auto const &lhs, auto const &rhs) { return lhs.delta_sum > rhs.delta_sum; })>();
        to_visits.push({0, 0});
        for (uint i = 0; i < k; i++) {
            auto const [curr, delta_sum] = to_visits.top();
            to_visits.pop();
            std::cout << min_price_sums[0] + delta_sum << ' ';

            usize sidetrack_id = city_last_sidetrack_ids[curr];
            while (sidetrack_id != ULONG_MAX) {
                auto const &[delta, end, next_sidetrack_id] = sidetracks[sidetrack_id];
                to_visits.push({end, delta_sum + delta});
                sidetrack_id = next_sidetrack_id;
            }
        }
        std::cout << '\n';
    }
}