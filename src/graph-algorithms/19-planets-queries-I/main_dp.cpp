#include <bit>
#include <climits>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

namespace {
// non-standard data types
using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;
using i8 = int8_t;
using i32 = int32_t;
using i64 = int64_t;
using usize = std::size_t;
using isize = std::make_signed_t<std::size_t>;
} // namespace

// (ref.) [CSES - Planet Queries I](https://usaco.guide/problems/cses-1750-planets-queries-i/solution)
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const u32 MAX_K = 1e9;
    const u32 MAX_DEPTH = std::numeric_limits<decltype(MAX_K)>::digits - 1 - std::countl_zero(MAX_K); // `2 ^ MAX_DEPTH` is the largest power of 2 not greater than MAX_K

    u32 num_planets;
    u32 num_queries;
    {
        std::cin >> num_planets >> num_queries;
    }

    auto nextss = std::vector<u32>((MAX_DEPTH + 1) * num_planets); // nextss[i * num_planets + j] is the `2^i`-th next element of `j`
    {
        {
            for (u32 j = 0; j < num_planets; j++) {
                std::cin >> nextss[j];
                nextss[j]--; // transform to 0-indexed (personal preference)
            }
        }
        for (u32 i = 1; i <= MAX_DEPTH; i++) {
            for (u32 j = 0; j < num_planets; j++) {
                nextss[i * num_planets + j] = nextss[(i - 1) * num_planets + nextss[(i - 1) * num_planets + j]];
            }
        }
    }

    {
        u32 start;
        u32 k;
        while (num_queries--) {
            std::cin >> start >> k;
            start--; // transform to 0-indexed (personal preference)

            u32 curr = start;
            for (u32 i = 0; i <= MAX_DEPTH; i++) {
                if (k & (1 << i)) {
                    curr = nextss[i * num_planets + curr];
                }
            }
            std::cout << curr + 1 << '\n';
        }
    }
}