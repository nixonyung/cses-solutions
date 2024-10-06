// (ref.) [[Tutorial] k shortest paths and Eppstein's algorithm - Algorithm 1](https://codeforces.com/blog/entry/102085#:~:text=Algorithm%201)

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

    {
        struct Path {
            uint end;
            ulong price_sum;
        };
        auto to_visits = std::priority_queue<
            Path,
            std::vector<Path>,
            decltype([](auto const &lhs, auto const &rhs) { return lhs.price_sum > rhs.price_sum; })>();
        auto visited_counter = std::vector<uint>(num_cities, 0);

        to_visits.push({0, 0});
        while (!to_visits.empty()) {
            auto const [curr, price_sum] = to_visits.top();
            to_visits.pop();
            if (visited_counter[curr] == k) continue;

            visited_counter[curr]++;
            if (curr == num_cities - 1) {
                std::cout << price_sum << ' ';
                if (visited_counter[num_cities - 1] == k) {
                    std::cout << '\n';
                    std::exit(0);
                }
            }

            for (auto const &[adj, price] : adjss[curr]) {
                if (visited_counter[adj] == k) continue;
                to_visits.push({adj, price_sum + price});
            }
        }
    }
}