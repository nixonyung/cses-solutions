#define VERSION_ORDERED_SET 1
#define VERSION_BLOCKED_VECTORS 2

#define VERSION VERSION_BLOCKED_VECTORS

#if VERSION == VERSION_ORDERED_SET
#include "../../lib/cses_io.hpp"
#include "../../lib/ordered_set.hpp"

int main() {
    cses::enable_fast_io();

    auto [n, k] = cses::read_tuple<int, int>();

    OrderedSet<int> childs;
    for (auto i = 1; i <= n; i++) {
        childs.insert(i);
    }

    auto child_idx = 0;
    for (auto i = 0; i < n; i++) {
        child_idx = (child_idx + k) % int(childs.size());
        auto it = childs.find_by_order(child_idx);
        std::cout << *it << ' ';
        childs.erase(it);
    }
    std::cout << '\n';
}
#elif VERSION == VERSION_BLOCKED_VECTORS
#include "../../lib/cses_io.hpp"
#include <cstdlib>
#include <vector>

int main() {
    cses::enable_fast_io();

    // (ref.) [Is there an alternative solution to CSES Josephus Problem II?](https://codeforces.com/blog/entry/102198)

    /*
    BLOCK_SIZE can be fine-tuned.

    A smaller BLOCK_SIZE improves erasing (for moving fewer elements & being more cache-friendly),
    but at the cost of spending more time on searching the correct block,
    and vice versa.
    */
    auto const BLOCK_SIZE = 2048;

    auto [n, k] = cses::read_tuple<int, int>();

    auto const &[quot, rem] = std::div(n, BLOCK_SIZE);
    auto blocks = std::vector<std::vector<int>>(quot + 1, std::vector<int>(BLOCK_SIZE));
    {
        for (auto i = 0; i < n; i++) {
            auto const &[block_idx, child_idx] = std::div(i, BLOCK_SIZE);
            blocks[block_idx][child_idx] = i + 1;
        }
        blocks.back().resize(rem);
    }

    auto block_idx = 0;
    auto child_idx = 0;
    for (auto i = 0; i < n; i++) {
        child_idx += k % (n - i); // `n-i` is the curr_num_childs
        while (child_idx >= blocks[block_idx].size()) {
            child_idx -= blocks[block_idx].size();
            block_idx++;
            if (block_idx >= blocks.size()) {
                block_idx = 0;
            }
        }
        std::cout << blocks[block_idx][child_idx] << ' ';
        blocks[block_idx].erase(blocks[block_idx].begin() + child_idx);
    }
    std::cout << '\n';
}
#endif