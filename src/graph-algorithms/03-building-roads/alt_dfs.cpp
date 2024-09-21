#include <bitset>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const uint MAX_N = 1e5;

    uint num_cities, num_old_edges;
    {
        std::cin >> num_cities >> num_old_edges;
    }

    auto adjss = std::vector<std::vector<uint>>(num_cities + 1);
    {
        uint from, to;
        for (int i = 0; std::cmp_less(i, num_old_edges); i++) {
            std::cin >> from >> to;
            adjss[from].push_back(to);
            adjss[to].push_back(from);
        }
    }

    auto unique_roots = std::vector<uint>();
    {
        auto visiteds = std::bitset<MAX_N + 1>();
        auto to_visits = std::stack<uint, std::vector<uint>>();
        for (int city = 1; std::cmp_less_equal(city, num_cities); city++) {
            if (visiteds[city]) { continue; }
            unique_roots.push_back(city);

            to_visits.push(city);
            while (!to_visits.empty()) {
                auto city = to_visits.top();
                to_visits.pop();

                if (visiteds[city]) { continue; }
                visiteds[city] = true;

                for (auto const &adj : adjss[city]) {
                    if (visiteds[adj]) { continue; }
                    to_visits.push(adj);
                }
            }
        }
    }
    std::cout << unique_roots.size() - 1 << '\n';
    if (unique_roots.size() > 1) {
        for (int i = 1; std::cmp_less(i, unique_roots.size()); i++) {
            std::cout << unique_roots[i - 1] << ' ' << unique_roots[i] << '\n';
        }
    }
}