#include "utils.hpp"
#include <vector>

int main() {
    enable_fast_io();

    // (ref.) [Is there an alternative solution to CSES Josephus Problem II?](https://codeforces.com/blog/entry/102198)

    /*
    BLOCK_SIZE can be fine-tuned.

    A smaller BLOCK_SIZE improves erasing (for moving fewer elements & being more cache-friendly),
    but at the cost of spending more time on searching the correct block,
    and vice versa.
    */
    auto const BLOCK_SIZE = 2048;

    auto n = read<uint>();
    auto k = read<uint>();

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
    ulong pos = 0;
    for (auto i : iota(0U, n)) {
        pos += k % (n - i); // `n-i` is the curr_num_childs
        while (pos >= blocks[block_idx].size()) {
            pos -= blocks[block_idx].size();
            block_idx++;
            if (block_idx >= blocks.size()) {
                block_idx = 0;
            }
        }
        std::cout << blocks[block_idx][pos] << ' ';
        blocks[block_idx].erase(blocks[block_idx].begin() + pos);
    }
    std::cout << '\n';
}