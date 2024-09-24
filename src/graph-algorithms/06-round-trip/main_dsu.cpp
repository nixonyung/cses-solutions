// correct implementation but outputs are different from tests

#include "disjoint_set_union.hpp"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>

namespace {
struct ToVisit {
    uint32_t city_id;
    size_t curr_path_len;
};
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t num_cities;
    uint32_t num_roads;
    {
        std::cin >> num_cities >> num_roads;
    }

    auto dsu = DisjointSetUnion(num_cities + 1);
    {
        auto adjss = std::vector<std::vector<uint32_t>>(num_cities + 1);
        {
            uint32_t city1;
            uint32_t city2;
            for (uint32_t i = 1; i <= num_roads; i++) {
                std::cin >> city1 >> city2;
                adjss[city1].push_back(city2);
                adjss[city2].push_back(city1);

                if (dsu.is_connected(city1, city2)) {
                    // cycle detected, run dsu on city1 to print the cycle
                    auto visited_at_path_idxs = std::vector<size_t>(num_cities + 1, 0); // 1-indexed
                    auto path = std::vector<uint32_t>();

                    auto to_visits = std::stack<ToVisit, std::vector<ToVisit>>();
                    to_visits.push({city1, 0});
                    while (!to_visits.empty()) {
                        auto const [city_id, curr_path_len] = to_visits.top();
                        to_visits.pop();

                        while (path.size() > curr_path_len) path.pop_back();
                        path.push_back(city_id);
                        visited_at_path_idxs[city_id] = path.size();

                        for (auto const &adj : adjss[city_id]) {
                            if (visited_at_path_idxs[adj] == 0) {
                                to_visits.push({adj, path.size()});
                            } else {
                                // found a cycle, i.e. path starts and ends with the same city
                                size_t cycle_len = path.size() - visited_at_path_idxs[adj] + 1 +
                                                   1; // also count adj
                                if (cycle_len >= 4) { // exclude paths revisiting the parent, e.g. "1 2 1"
                                    std::cout << path.size() + 2 - visited_at_path_idxs[adj] << '\n';
                                    for (size_t i = visited_at_path_idxs[adj] - 1; i < path.size(); i++) {
                                        std::cout << path[i] << ' ';
                                    }
                                    std::cout << adj << " \n";
                                    std::exit(0);
                                }
                            }
                        }
                    }
                } else {
                    dsu.connect(city1, city2);
                }
            }
        }
    }
    std::cout << "IMPOSSIBLE\n";
}