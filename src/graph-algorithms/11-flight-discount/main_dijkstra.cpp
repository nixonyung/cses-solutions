#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

// custom primitive data types
typedef unsigned int uint;
typedef unsigned long ulong;
typedef std::size_t usize;
typedef std::make_signed_t<std::size_t> isize;

namespace {
struct Connection {
    uint end_city_id;
    uint price;
};
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint num_cities;
    uint num_connections;
    {
        std::cin >> num_cities >> num_connections;
    }

    auto adjss = std::vector<std::vector<Connection>>(num_cities);
    {
        uint start;
        uint end;
        uint price;
        for (uint i = 0; i < num_connections; i++) {
            std::cin >> start >> end >> price;
            // transform to 0-indexed (personal preference)
            start--;
            end--;
            adjss[start].push_back({end, price});
        }
    }

    /*
    min_discounted_prices[i] = min(
        min_prices[i-1] + prices[i]/2,
        min_discounted_prices[i-1] + prices[i],
    )
    */
    auto min_prices = std::vector<ulong>(num_cities, ULONG_MAX);
    auto min_discounted_prices = std::vector<ulong>(num_cities, ULONG_MAX);
    {
        struct ToVisit {
            uint city_id;
            ulong prices_sum;
        };
        auto to_visits = std::priority_queue<
            ToVisit,
            std::vector<ToVisit>,
            decltype([](auto const &lhs, auto const &rhs) { return lhs.prices_sum > rhs.prices_sum; })>();
        // fill in min_prices
        {
            to_visits.push({0, 0});
            while (!to_visits.empty()) {
                auto const [curr_city, prices_sum] = to_visits.top();
                to_visits.pop();

                if (min_prices[curr_city] != ULONG_MAX) continue;
                min_prices[curr_city] = prices_sum;

                for (auto const &[adj, price] : adjss[curr_city]) {
                    if (min_prices[adj] != ULLONG_MAX) continue;
                    to_visits.push({adj, prices_sum + price});
                }
            }
        }
        // fill in min_discounted_prices
        {
            to_visits.push({0, 0});
            while (!to_visits.empty()) {
                auto const [curr_city, prices_sum] = to_visits.top();
                to_visits.pop();

                if (min_discounted_prices[curr_city] != ULONG_MAX) continue;
                min_discounted_prices[curr_city] = prices_sum;

                for (auto const &[adj, price] : adjss[curr_city]) {
                    if (min_discounted_prices[adj] != ULLONG_MAX) continue;
                    to_visits.push(
                        {adj,
                         std::min(
                             min_prices[curr_city] + price / 2,
                             min_discounted_prices[curr_city] + price
                         )
                        }
                    );
                }
            }
        }
    }
    std::cout << min_discounted_prices[num_cities - 1] << '\n';
}