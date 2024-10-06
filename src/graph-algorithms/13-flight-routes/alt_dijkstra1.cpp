// (ref.) [Flight Routes](https://codeforces.com/blog/entry/118068#:~:text=Flight%20Routes)
// idea: use modified Dijkstra and instead discard paths if they have higher `price_sum` than the k-th shortest path ending at the same city, as they will never lead to k shortest paths to `end`
// implementation is not optimized: no need to use heaps on each city given that Dijkstra will visit paths in ascending order anyway

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
    uint end;
    uint price;
};
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint num_cities;
    uint num_routes;
    uint k;
    {
        std::cin >> num_cities >> num_routes >> k;
    }

    auto adjss = std::vector<std::vector<Route>>(num_cities);
    {
        uint start;
        uint end;
        uint price;
        for (uint i = 0; i < num_routes; i++) {
            std::cin >> start >> end >> price;
            // transform to 0-indexed (personal preference)
            adjss[start - 1].push_back({end - 1, price});
        }
    }

    auto k_min_price_sumss = std::vector<
        std::priority_queue<
            ulong,
            std::vector<ulong>,
            decltype([](auto const &lhs, auto const &rhs) { return lhs < rhs; })>>(num_cities);
    {
        struct ToVisit {
            uint city;
            ulong price_sum;
        };
        auto to_visits = std::priority_queue<
            ToVisit,
            std::vector<ToVisit>,
            decltype([](auto const &lhs, auto const &rhs) { return lhs.price_sum > rhs.price_sum; })>();
        to_visits.push({0, 0});
        while (!to_visits.empty()) {
            auto const [curr, price_sum] = to_visits.top();
            to_visits.pop();
            if (k_min_price_sumss[curr].size() == k && price_sum >= k_min_price_sumss[curr].top()) continue;

            if (k_min_price_sumss[curr].size() == k) k_min_price_sumss[curr].pop();
            k_min_price_sumss[curr].push(price_sum);
            if (curr == num_cities - 1 && k_min_price_sumss[curr].size() == k) {
                // print k_min_price_sumss[num_cities - 1] from the smallest price_sum
                auto ans = std::vector<ulong>(k);
                {
                    for (uint i = 0; i < k; i++) {
                        ans[k - 1 - i] = k_min_price_sumss[num_cities - 1].top();
                        k_min_price_sumss[num_cities - 1].pop();
                    }
                }
                for (uint i = 0; i < k; i++) {
                    std::cout << ans[i] << ' ';
                }
                std::cout << '\n';
                std::exit(0);
            }

            for (auto const &[adj, price] : adjss[curr]) {
                to_visits.push({adj, price_sum + price});
            }
        }
    }
}