#include "utils.hpp"

int main() {
    const ulong MOD = 1e9 + 7;

    enable_fast_io();

    auto num_rows = read<uint>();
    auto num_cols = read<uint>();
    // impossible if n*m is odd because the available tiles always fill 2 cells
    if ((num_rows & 1) && (num_cols & 1)) {
        std::cout << 0 << '\n';
        std::exit(0);
    }

    // (ref.) [DP on Broken Profile](https://usaco.guide/adv/dp-more?lang=cpp#dp-on-broken-profile)

    /*
    num_wayss[prev_cells_configuration] for a cell (row, col)
    is the number of ways where all cells at or before (row, col-1) are covered
    and the prev n processed cells are in the given configuration
    where the k-th bit in the configuration refers to whether the prev processed cell at row k is covered.
    */
    auto num_wayss = std::vector<ulong>(1U << num_rows, 0); // only store the result from the prev cell
    {
        // initial state: treat cells at boundary as covered
        num_wayss[(1U << num_rows) - 1] = 1;

        // recurrence
        //
        // available actions:
        // - adding a 1x2 tile to cover (row, col-1) and (row, col)
        // - adding a 2x1 tile to cover (row-1, col) and (row, col)
        auto next_num_wayss = decltype(num_wayss)(1U << num_rows); // preallocate memory
        // traverse cells col-by-col then row-by-row,
        for (auto _ : iota(0U, num_cols)) {
            for (auto row : iota(0U, num_rows)) {
                { // fill next_num_wayss
                    for (auto prev_cells_configuration : iota(0U, 1U << num_rows)) {
                        // note that:
                        // prev_cells_configuration for next_num_wayss includes the curr cell,
                        // but prev_cells_configuration for num_wayss DOES NOT (and instead inclues (row, col-1))

                        // for configurations that requires to cover the curr cell
                        if (prev_cells_configuration & (1U << row)) {
                            // count num_ways adding a 1x2 tile to prev configurations without (row, col-1) covered
                            next_num_wayss[prev_cells_configuration] = num_wayss[prev_cells_configuration & ~(1U << row)];
                        }
                        // for configurations that requires not to cover the curr cell
                        else {
                            // count num_ways adding nothing to prev configurations with (row, col-1) covered
                            next_num_wayss[prev_cells_configuration] = num_wayss[prev_cells_configuration | (1U << row)];
                        }
                        // for configurations that requires to cover the prev cell and the curr cell
                        if (row > 0 && (prev_cells_configuration & (1U << row)) && (prev_cells_configuration & (1U << (row - 1)))) {
                            // count num_ways adding a 2x1 tile to prev configurations with (row-1, col) covered
                            next_num_wayss[prev_cells_configuration] += num_wayss[prev_cells_configuration & ~(1U << (row - 1))];
                        }
                    }
                    std::ranges::for_each(
                        next_num_wayss,
                        [](auto &num_ways) { num_ways %= MOD; }
                    );
                }
                std::swap(num_wayss, next_num_wayss);
            }
        }
    }
    // ans is num_ways where cells before (n-1, m-2) must be covered
    // and all the prev processed cells (i.e. cells at col m-1) are covered
    std::cout << num_wayss[(1U << num_rows) - 1] << '\n';
}