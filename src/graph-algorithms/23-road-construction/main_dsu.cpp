#include "disjoint_set_union.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>

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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    u32 num_cities;
    u32 num_roads;
    {
        std::cin >> num_cities >> num_roads;
    }

    {
        auto dsu = DisjointSetUnion(num_cities);
        usize max_component_size = 0;

        u32 start;
        u32 end;
        while (num_roads--) {
            std::cin >> start >> end;
            // transform to 0-indexed (personal preference)
            start--;
            end--;

            auto const &root = dsu.connect(start, end);
            max_component_size = std::max(max_component_size, root.num_descendants);
            std::cout << dsu.num_roots() << ' ' << max_component_size << '\n';
        }
    }
}