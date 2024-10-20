#include "dfs.hpp"
#include "io.hpp"
#include "primitives.hpp"
#include <cstdlib>
#include <vector>

// (ref.) [De Bruijn sequence - Construction](https://www.wikiwand.com/en/articles/De_Bruijn_sequence#Construction)
// (ref.) [Algorithm for finding a Hamiltonian Path in a DAG](https://stackoverflow.com/questions/16124844/algorithm-for-finding-a-hamiltonian-path-in-a-dag)
// correct implementation but outputs are different from tests
int main() {
    enable_fast_io();

    auto n = read<U32>();
    const U32 mask = (1U << n) - 1;

    auto nextss = std::vector<std::vector<U32>>(1U << n);
    {
        for (U32 i = 0; i < 1U << n; i++) {
            nextss[i].push_back((i << 1) & mask);
            nextss[i].push_back(((i << 1) & mask) | 1);
        }
    }

    for (U32 i = 0; i < n - 1; i++) std::cout << 0; // the first node of the Hamiltonian path is (n-1) zeroes, so print (n-2) zeroes first
    {
        auto dfs = DFS(1U << n, nextss);
        dfs.push(0);
        for (auto to_visit = dfs.pop(); to_visit.id != UINT_MAX; to_visit = dfs.pop()) {
            auto const &[curr, phase] = to_visit;
            if (phase == DFS<>::Phase::BACKTRACKING) {
                std::cout << (curr >> (n - 1)); // optimization: ndoes are reported in reverse order, so append MSB to the sequence
            }
            // no need to invalidate having cycles
        }
    }
    std::cout << '\n';
}