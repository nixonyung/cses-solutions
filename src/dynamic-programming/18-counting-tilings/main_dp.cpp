// (ref.) [DP on Broken Profile](https://usaco.guide/adv/dp-more?lang=cpp#dp-on-broken-profile)

#include <algorithm>
#include <iostream>
#include <vector>

namespace {
const unsigned long MOD = 1e9 + 7;
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned NUM_ROWS;
    unsigned NUM_COLS;
    {
        std::cin >> NUM_ROWS >> NUM_COLS;
    }
    // impossible if the number of cells is odd because the available actions always fill 2 cells
    if ((NUM_ROWS & 1) && (NUM_COLS & 1)) {
        std::cout << 0 << '\n';
        return 0;
    }

    /*
    num_wayss[bitmask] for a cell represents the number of ways where
    the prev N cells (including the cell owning num_wayss) has `bitmask` configuration
    (`bitmask & (1 << row)` is 0 means the cell is not covered, 1 means the cell is covered)
    */
    auto num_wayss = std::vector<unsigned long>(1U << NUM_ROWS, 0); // optimization: only store the result from the prev CELL
    {
        num_wayss[(1U << NUM_ROWS) - 1] = 1; // initial condition: "cover" all cells at boundary

        auto next_num_wayss = num_wayss;
        for (unsigned col = 0; col < NUM_COLS; col++) {
            for (unsigned row = 0; row < NUM_ROWS; row++) {
                for (unsigned i = 0; i < (1U << NUM_ROWS); i++) { // iterate bitmasks
                    // (ref.) [How to set, clear, and toggle a single bit](https://stackoverflow.com/questions/47981/how-to-set-clear-and-toggle-a-single-bit)
                    next_num_wayss[i] =
                        (((i & (1U << row))
                              // for configurations that requires to cover the curr cell,
                              // count num_ways for adding a 1x2 (horizontal) tile to prev configurations where the cell (row, col-1) is not already covered
                              ? num_wayss[i & ~(1U << row)]
                              // for configurations that requires not to cover the curr cell,
                              // count num_ways for adding nothing to prev configurations where the cell (row, col-1) is already covered
                              : num_wayss[i | (1U << row)])
                         + ((row > 0
                             && (i & (1U << row))
                             && (i & (1U << (row - 1)))
                            )
                                // for configurations that requires to cover the prev cell and the curr cell,
                                // count num_ways for adding a 2x1 (vertical) tile to prev configurations where the cell (row-1, col) is not already covered
                                ? num_wayss[i & ~(1U << (row - 1))]
                                : 0)
                        )
                        % MOD;
                }
                std::swap(num_wayss, next_num_wayss);
            }
        }
    }
    std::cout << num_wayss[(1U << NUM_ROWS) - 1] << '\n';
}