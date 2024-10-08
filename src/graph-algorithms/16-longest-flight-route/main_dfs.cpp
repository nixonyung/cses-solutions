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

// (ref.) [Longest path problem - Acyclic graphs](https://www.wikiwand.com/en/articles/Longest_path_problem#Acyclic_graphs)
// (ref.) [Topological Sorting](https://cp-algorithms.com/graph/topological-sort.html)
// correct implementation but outputs are different from tests
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

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

    auto longest_flight_lens = std::vector<uint>(num_cities, 0);
    auto updated_bys = std::vector<uint>(num_cities, UINT_MAX);
    {
        longest_flight_lens[num_cities - 1] = 1;

        // "3-colors DFS"
        enum class Color : char {
            NONE,
            IN_PATH,
            HANDLED,
        };
        auto colors = std::vector<Color>(num_cities, Color::NONE);

        auto to_visits = std::stack<uint>();
        to_visits.push(0);
        while (!to_visits.empty()) {
            auto const curr = to_visits.top();
            to_visits.pop();

            switch (colors[curr]) {
            case Color::HANDLED:
                break;
            case Color::NONE: {
                to_visits.push(curr); // revisit curr AFTER visiting all adjs
                for (auto const &adj : adjss[curr]) {
                    if (colors[adj] != Color::NONE) continue;
                    to_visits.push(adj);
                }
                colors[curr] = Color::IN_PATH;
            } break;
            case Color::IN_PATH: {
                for (auto const &adj : adjss[curr]) {
                    if (
                        longest_flight_lens[adj] != 0 &&
                        longest_flight_lens[adj] + 1 > longest_flight_lens[curr]
                    ) {
                        longest_flight_lens[curr] = longest_flight_lens[adj] + 1;
                        updated_bys[curr] = adj;
                    }
                }
                colors[curr] = Color::HANDLED;
            } break;
            }
        }
    }
    if (longest_flight_lens[0] == 0) {
        std::cout << "IMPOSSIBLE\n";
    } else {
        auto const &flight_len = longest_flight_lens[0];
        std::cout << flight_len << '\n';

        auto path = std::vector<uint>(flight_len);
        {
            uint curr = 0;
            for (uint i = 0; i < flight_len; i++) {
                path[i] = curr;
                curr = updated_bys[curr];
            }
        }
        for (auto const &city : path) {
            std::cout << city + 1 << ' ';
        }
        std::cout << '\n';
    }
}