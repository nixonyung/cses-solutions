#include "io.hpp"
#include "primitives.hpp"
#include <vector>

// (ref.) [Hamiltonian Path (Using Dynamic Programming)](https://www.geeksforgeeks.org/hamiltonian-path-using-dynamic-programming/)
int main() {
    enable_fast_io();

    const U64 MOD = 1e9 + 7;

    auto num_citys = read<U32>();
    auto num_flights = read<U32>();
    auto prevss = std::vector<std::vector<U32>>(num_citys);
    {
        for (U32 i = 0; i < num_flights; i++) {
            // peronsal preference: transform to 0-indexed
            auto prev = read<U32>() - 1;
            prevss[read<U32>() - 1].push_back(prev);
        }
    }

    auto num_paths = std::vector<std::vector<U64>>(1 << num_citys, std::vector<U64>(num_citys, 0));
    {
        num_paths[1][0] = 1;

        for (U32 configuration = 1; configuration < (1U << num_citys); configuration += 2) { // iterate configuration in ascending order so that `num_paths[configuration ^ (1 << curr)][prev]` must be already converged
            for (U32 curr = 0; curr < num_citys; curr++) {
                if (!(configuration & (1 << curr))) continue;
                for (auto const &prev : prevss[curr]) {
                    if (!(configuration & (1 << prev))) continue;
                    num_paths[configuration][curr] += num_paths[configuration ^ (1 << curr)][prev];
                }
                num_paths[configuration][curr] %= MOD;
            }
        }
    }
    std::cout << num_paths[(1U << num_citys) - 1][num_citys - 1] << '\n';
}