// (ref.) [Is there an alternative solution to CSES Josephus Problem II?](https://codeforces.com/blog/entry/102198)
// (ref.) [Sqrt Decomposition](https://cp-algorithms.com/data_structures/sqrt_decomposition.html)

#include <cmath>
#include <iostream>
#include <vector>

namespace {
const unsigned MIN_BLOCK_SIZE = 2048;
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned K;
    {
        std::cin >> N >> K;
    }

    /*
    Setting BLOCK_SIZE = sqrt(N) has the best theoretical complexity, but it can also be fine-tuned.
        A smaller BLOCK_SIZE improves erasing (for moving fewer elements & being more cache-friendly),
        but at the cost of spending more time on searching the correct block, and vice versa.
    */
    unsigned const block_size = (N >= MIN_BLOCK_SIZE * MIN_BLOCK_SIZE)
                                    ? (1 << (32 - std::countl_zero((unsigned)std::sqrt(N))))
                                    : MIN_BLOCK_SIZE;
    auto blocks = std::vector<std::vector<unsigned>>();
    {
        auto const [quot, rem] = std::ldiv(N, block_size);
        blocks.resize(quot + 1, decltype(blocks)::value_type(block_size));

        unsigned block_idx = 0;
        unsigned child_idx = 0;
        for (unsigned i = 0; i < N; i++) {
            blocks[block_idx][child_idx] = i + 1;
            child_idx++;
            if (child_idx == block_size) {
                block_idx++;
                child_idx = 0;
            }
        }
        blocks.back().resize(rem);
    }

    {
        unsigned long pos = 0;
        unsigned block_idx = 0;
        for (unsigned i = 0; i < N; i++) {
            pos += K % (N - i); // `N-i` is the current num_childs
            while (pos >= blocks[block_idx].size()) {
                pos -= blocks[block_idx].size();
                block_idx++;
                if (block_idx >= blocks.size()) block_idx = 0;
            }
            std::cout << blocks[block_idx][pos] << ' ';
            blocks[block_idx].erase(blocks[block_idx].begin() + pos);
        }
    }
    std::cout << '\n';
}