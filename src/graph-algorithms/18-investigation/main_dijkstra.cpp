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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const ulong MOD = 1e9 + 7;

    uint num_cities;
    uint num_routes;
    {
        std::cin >> num_cities >> num_routes;
    }

    struct Adj {
        uint city_id;
        uint price;
    };
    auto adjss = std::vector<std::vector<Adj>>(num_cities);
    {
        uint start;
        uint end;
        uint price;
        for (uint i = 0; i < num_routes; i++) {
            std::cin >> start >> end >> price;
            // transform to 0-indexed (personal preference)
            start--;
            end--;

            adjss[start].push_back({end, price});
        }
    }

    struct State {
        ulong min_price_sum; // price_sum starting from city0
        ulong num_routes;
        uint min_num_flights;
        uint max_num_flights;
    };
    auto states = std::vector<State>(num_cities, {ULONG_MAX, 0, UINT_MAX, 0});
    {
        struct ToVisit {
            uint city_id;
            ulong price_sum;
            uint parent_id;
        };
        auto to_visits = std::priority_queue<
            ToVisit,
            std::vector<ToVisit>,
            decltype([](auto const &lhs, auto const &rhs) { return lhs.price_sum > rhs.price_sum; })>();
        to_visits.push({0, 0, UINT_MAX});
        while (!to_visits.empty()) {
            auto const [curr, price_sum, parent] = to_visits.top();
            to_visits.pop();

            // using states[parent] is valid because it has converged
            if (states[curr].min_price_sum == ULONG_MAX) {
                states[curr] = {
                    price_sum,
                    (parent == UINT_MAX) ? 1 : states[parent].num_routes,
                    (parent == UINT_MAX) ? 0 : states[parent].min_num_flights + 1,
                    (parent == UINT_MAX) ? 0 : states[parent].max_num_flights + 1
                };
            } else if (states[curr].min_price_sum == price_sum) {
                states[curr].num_routes = (states[curr].num_routes + states[parent].num_routes) % MOD;
                states[curr].min_num_flights = std::min(states[curr].min_num_flights, states[parent].min_num_flights + 1);
                states[curr].max_num_flights = std::max(states[curr].max_num_flights, states[parent].max_num_flights + 1);
                continue;
            } else continue;

            for (auto const &[adj, price] : adjss[curr]) {
                if (states[adj].min_price_sum != ULONG_MAX) continue;
                to_visits.push({adj, price_sum + price, curr});
            }
        }
    }
    std::cout << states[num_cities - 1].min_price_sum << ' '
              << states[num_cities - 1].num_routes << ' '
              << states[num_cities - 1].min_num_flights << ' '
              << states[num_cities - 1].max_num_flights << '\n';
}