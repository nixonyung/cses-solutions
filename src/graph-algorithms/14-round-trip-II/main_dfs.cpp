#include <bitset>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>

// custom primitive data types
typedef unsigned int uint;
typedef unsigned long ulong;
typedef std::size_t usize;
typedef std::make_signed_t<std::size_t> isize;

// correct implementation but outputs are different from tests
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const uint MAX_NUM_CITIES = 1e5;

    uint num_cities;
    uint num_routes;
    {
        std::cin >> num_cities >> num_routes;
    }

    auto adjss = std::vector<std::vector<uint>>(num_cities);
    {
        uint start;
        uint end;
        for (uint i = 0; i < num_routes; i++) {
            std::cin >> start >> end;
            // transform to 0-indexed (personal preference)
            start--;
            end--;

            adjss[start].push_back(end);
        }
    }

    auto city_to_path_len = std::vector<usize>(num_cities, ULONG_MAX);
    auto path = std::vector<uint>();
    {
        struct ToVisit {
            usize path_len;
            uint city_id;
        };
        auto to_visits = std::stack<ToVisit>();
        auto visiteds = std::bitset<MAX_NUM_CITIES>();

        for (uint i = 0; i < num_cities; i++) {
            if (visiteds[i]) continue;
            to_visits.push({0, i});

            while (!to_visits.empty()) {
                auto const [path_len, curr] = to_visits.top();
                to_visits.pop();

                while (path.size() > path_len) {
                    city_to_path_len[path.back()] = ULONG_MAX;
                    path.pop_back();
                }
                path.push_back(curr);

                if (city_to_path_len[curr] != ULONG_MAX) {
                    usize cycle_len = path.size() + 1 - city_to_path_len[curr];
                    if (cycle_len < 3) continue;
                    std::cout << cycle_len << '\n';
                    for (usize i = city_to_path_len[curr] - 1; i < path.size(); i++) {
                        std::cout << path[i] + 1 << ' ';
                    }
                    std::cout << '\n';
                    std::exit(0);
                }
                if (visiteds[curr]) continue; // optimization: revisiting cities will not lead to new cycles
                city_to_path_len[curr] = path.size();
                visiteds[curr] = true;

                for (auto const &adj : adjss[curr]) {
                    to_visits.push({path.size(), adj});
                }
            }
        }
    }
    std::cout << "IMPOSSIBLE\n";
}