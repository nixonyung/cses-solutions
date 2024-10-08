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

// (ref.) [Longest path problem - Acyclic graphs](https://www.wikiwand.com/en/articles/Longest_path_problem#Acyclic_graphs)
// (ref.) [Kahn's algorithm for Topological Sorting](https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/)
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint num_cities;
    uint num_routes;
    {
        std::cin >> num_cities >> num_routes;
    }

    auto childss = std::vector<std::vector<uint>>(num_cities);
    auto parentss = std::vector<std::vector<uint>>(num_cities);
    {
        uint start;
        uint end;
        for (uint i = 0; i < num_routes; i++) {
            std::cin >> start >> end;
            // transform to 0-indexed (personal preference)
            start--;
            end--;

            childss[start].push_back(end);
            parentss[end].push_back(start);
        }
    }

    auto longest_flight_lens = std::vector<uint>(num_cities, 0);
    auto updated_bys = std::vector<uint>(num_cities, UINT_MAX);
    {
        longest_flight_lens[0] = 1;

        auto to_visits = std::queue<uint>();
        auto num_unvisited_parents = std::vector<usize>(num_cities);
        {
            for (uint i = 0; i < num_cities; i++) {
                num_unvisited_parents[i] = parentss[i].size();
                if (num_unvisited_parents[i] == 0) to_visits.push(i);
            }
        }
        while (!to_visits.empty()) {
            auto const curr = to_visits.front();
            to_visits.pop();

            for (auto const &parent : parentss[curr]) {
                if (
                    longest_flight_lens[parent] != 0 && // exclude parents unreachable from city0
                    longest_flight_lens[parent] + 1 > longest_flight_lens[curr]
                ) {
                    longest_flight_lens[curr] = longest_flight_lens[parent] + 1;
                    updated_bys[curr] = parent;
                }
            }
            for (auto const &child : childss[curr]) {
                num_unvisited_parents[child]--;
                if (num_unvisited_parents[child] == 0) to_visits.push(child);
            }
        }
    }
    if (longest_flight_lens[num_cities - 1] == 0) {
        std::cout << "IMPOSSIBLE\n";
    } else {
        auto const &flight_len = longest_flight_lens[num_cities - 1];
        std::cout << flight_len << '\n';

        auto path = std::vector<uint>(flight_len);
        {
            uint curr = num_cities - 1;
            for (int i = flight_len - 1; i >= 0; i--) {
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