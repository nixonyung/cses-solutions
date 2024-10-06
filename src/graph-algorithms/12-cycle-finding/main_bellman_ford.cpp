// (ref.) [Finding a negative cycle in the graph](https://cp-algorithms.com/graph/finding-negative-cycle-in-graph.html)

#include <algorithm>
#include <bitset>
#include <climits>
#include <iostream>
#include <vector>

// custom primitive data types
typedef unsigned int uint;
typedef unsigned long ulong;
typedef std::size_t usize;
typedef std::make_signed_t<std::size_t> isize;

namespace {
struct Edge {
    uint start;
    uint end;
    int weight;
};
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const uint MAX_NUM_NODES = 2500;

    uint num_nodes;
    uint num_edges;
    {
        std::cin >> num_nodes >> num_edges;
    }

    auto edges = std::vector<Edge>(num_edges);
    {
        for (uint i = 0; i < num_edges; i++) {
            std::cin >> edges[i].start >> edges[i].end >> edges[i].weight;
            // transform to 0-indexed (personal preference)
            edges[i].start--;
            edges[i].end--;
        }
    }

    auto updated_bys = std::vector<uint>(num_nodes, UINT_MAX);
    uint last_updated = UINT_MAX;
    {
        auto updateds = std::bitset<MAX_NUM_NODES>(); // optimization: SPFA
        auto next_updateds = std::bitset<MAX_NUM_NODES>();
        updateds.set();

        auto min_weight_sums = std::vector<long>(num_nodes, 0); // initialized to arbitrary nonnegative value (something that a negative cycle can keep overwritting)
        for (uint epoch = 0; epoch < num_nodes; epoch++) {
            next_updateds.reset();
            for (auto const &[start, end, weight] : edges) {
                if (!updateds[start] || min_weight_sums[start] + weight >= min_weight_sums[end]) continue;
                min_weight_sums[end] = min_weight_sums[start] + weight;
                updated_bys[end] = start;
                next_updateds[end] = true;
                if (epoch == num_nodes - 1) {
                    last_updated = start;
                }
            }
            if (next_updateds.none()) break;
            updateds = next_updateds;
        }
    }
    if (last_updated != UINT_MAX) {
        // "`last_updated` will either lie in a negative weight cycle, or is reachable from it."
        // "To get the vertices that are guaranteed to lie in a negative cycle, starting from the vertex, pass through `updated_bys`  n  times."
        for (uint i = 0; i < num_nodes; i++) {
            last_updated = updated_bys[last_updated];
        }

        auto path = std::vector<uint>();
        {
            for (uint curr = last_updated; !(path.size() > 0 && curr == last_updated); curr = updated_bys[curr]) {
                path.push_back(curr);
            }
            path.push_back(last_updated);
            std::ranges::reverse(path);
        }
        std::cout << "YES\n";
        for (uint i = 0; i < path.size(); i++) {
            std::cout << path[i] + 1 << ' ';
        }
        std::cout << '\n';
    } else {
        std::cout << "NO\n";
    }
}