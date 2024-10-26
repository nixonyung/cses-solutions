#include "io.hpp"
#include "primitives.hpp"
#include <vector>

// (ref.) [Hamiltonian Path (Using Dynamic Programming)](https://www.geeksforgeeks.org/hamiltonian-path-using-dynamic-programming/)
int main() {
    enable_fast_io();

    const U64 MOD = 1e9 + 7;

    auto num_citys = read<U32>();
    auto num_flights = read<U32>();
    auto nextss = std::vector<std::vector<U32>>(num_citys);
    {
        for (U32 i = 0; i < num_flights; i++) {
            nextss[read<U32>() - 1].push_back(read<U32>() - 1); // peronsal preference: transform to 0-indexed
        }
    }

    auto num_paths = std::vector<std::vector<U64>>(1 << num_citys, std::vector<U64>(num_citys, 0));
    {
        num_paths[1][0] = 1;

        /*
        optimizations:
        - skip configurations without bit (1 << 0) set because it is trivial that `num_paths` without using city_0 must be 0
        - skip configurations with bit (1 << num_citys) set because intermediate configurations with the end city used can neber update the answer`num_paths[(1U << num_citys) - 1][num_citys - 1]`
          - e.g. configuration "1001" can neber lead to `num_paths[1111][3]` because city_3 is already used as an intermediate city
        */
        for (U32 configuration = 1; configuration < (1U << (num_citys - 1)); configuration += 2) { // iterate configuration in ascending order so that `num_paths[configuration][curr]` must be already converged
            for (U32 curr = 0; curr < num_citys; curr++) {
                if (num_paths[configuration][curr] == 0) continue;
                for (auto const &next : nextss[curr]) {
                    if (configuration & (1 << next)) continue;
                    num_paths[configuration | (1 << next)][next] += num_paths[configuration][curr];
                    num_paths[configuration | (1 << next)][next] %= MOD;
                }
            }
        }
    }
    std::cout << num_paths[(1U << num_citys) - 1][num_citys - 1] << '\n';
}