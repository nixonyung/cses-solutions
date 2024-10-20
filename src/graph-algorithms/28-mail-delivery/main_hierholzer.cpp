#include "disjoint_set_union.hpp"
#include "io.hpp"
#include "primitives.hpp"
#include <cstdlib>
#include <stack>
#include <vector>

// (ref.) [Eulerian path](https://cp-algorithms.com/graph/euler_path.html)
// (ref.) [Eulerian path - Properties](https://www.wikiwand.com/en/articles/Eulerian_path#Properties)
// (ref.) [Hierholzer's algorithm](https://www.wikiwand.com/en/articles/Eulerian_path#Hierholzer%27s_algorithm)
// correct implementation but outputs are different from tests
int main() {
    enable_fast_io();

    auto num_citys = read<U32>();
    auto num_streets = read<U32>();

    struct Street {
        U32 id;
        U32 end;
    };
    auto streetss = std::vector<std::vector<Street>>(num_citys);
    {
        auto dsu = DisjointSetUnion(num_citys);

        for (U32 i = 0; i < num_streets; i++) {
            // peronsal preference: transform to 0-indexed
            auto start = read<U32>() - 1;
            auto end = read<U32>() - 1;
            streetss[start].push_back({i, end});
            streetss[end].push_back({i, start});
            dsu.connect(start, end);
        }
        for (U32 i = 0; i < num_citys; i++) {
            if (
                // any city with streets must be reachable from city_0
                (streetss[i].size() != 0 && !dsu.is_connected(i, 0)) ||
                // an Euler cycle exist iff all nodes have even degree
                (streetss[i].size() & 1)
            ) {
                std::cout << "IMPOSSIBLE\n";
                std::exit(0);
            }
        }
    }

    {
        auto to_visits = std::stack<U32>();
        auto street_takens = std::vector<bool>(num_streets, false);
        auto street_idxs = std::vector<U32>(num_citys, 0); // optimization: maintain "streets[:street_idx+1] must be taken" to save searching time

        to_visits.push(0);
        while (!to_visits.empty()) {
            auto const curr = to_visits.top();

            while (street_idxs[curr] < streetss[curr].size() && street_takens[streetss[curr][street_idxs[curr]].id]) {
                street_idxs[curr]++;
            }
            if (street_idxs[curr] == streetss[curr].size()) {
                std::cout << curr + 1 << ' ';
                to_visits.pop();
                continue;
            }
            auto const &[next_street_id, next] = streetss[curr][street_idxs[curr]];
            street_takens[next_street_id] = true;
            to_visits.push(next);
            street_idxs[curr]++;
        }
    }
    std::cout << '\n';
}