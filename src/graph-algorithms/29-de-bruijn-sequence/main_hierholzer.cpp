#include "io.hpp"
#include "primitives.hpp"
#include <cstdlib>
#include <stack>
#include <vector>

// (ref.) [De Bruijn sequence - Construction](https://www.wikiwand.com/en/articles/De_Bruijn_sequence#Construction)
// (ref.) [De Bruijn Sequences](https://usaco.guide/adv/eulerian-tours?lang=cpp#de-bruijn-sequences)
// (ref.) [Hierholzer's algorithm](https://www.wikiwand.com/en/articles/Eulerian_path#Hierholzer's_algorithm)
// correct implementation but outputs are different from tests
int main() {
    enable_fast_io();

    auto n = read<U32>();
    if (n == 1) {
        std::cout << "10\n";
        return 0;
    }
    const U32 mask = (1U << (n - 1)) - 1;

    for (U32 i = 0; i < n - 2; i++) std::cout << 0; // the first node of the Eulerian path is (n-1) zeroes, so print (n-2) zeroes first
    {
        auto to_visits = std::stack<U32>();
        auto edge_idxs = std::vector<U32>(1U << (n - 1), 0);

        to_visits.push(0);
        while (!to_visits.empty()) {
            auto const curr = to_visits.top();
            if (edge_idxs[curr] == 2) {         // 2 choices for each node (append 0 or 1), so `curr_edge_idx` == 2 means no more unused choices
                std::cout << (curr >> (n - 2)); // optimization: ndoes are reported in reverse order, so append MSB to the sequence
                to_visits.pop();
                continue;
            }
            to_visits.push(((curr << 1) & mask) | edge_idxs[curr]);
            edge_idxs[curr]++;
        }
    }
    std::cout << '\n';
}