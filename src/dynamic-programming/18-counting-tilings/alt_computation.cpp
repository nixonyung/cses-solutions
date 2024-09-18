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

    /*
    num_wayss[next_cells_configuration] for a cell (row, col)
    is the number of ways where all cells at or before (row, col) are covered
    and the next n cells are in the given configuration
    where the k-th bit in the configuration refers to whether the next cell at row k is covered.
    */
    auto num_wayss = std::vector<ulong>(1U << num_rows, 0); // only store the result from the prev cell
    {
        // initial state
        num_wayss[0] = 1;

        // recurrence
        //
        // available actions:
        // - adding a 1x2 tile to cover (row, col) and (row, col+1)
        // - adding a 2x1 tile to cover (row, col) and (row+1, col)
        auto next_num_wayss = decltype(num_wayss)(1U << num_rows); // preallocate memory
        // traverse cells col-by-col then row-by-row,
        for (auto _ : iota(0U, num_cols)) {
            for (auto row : iota(0U, num_rows)) {
                { // fill next_num_wayss
                    std::ranges::fill(next_num_wayss, 0);
                    for (auto next_cells_configuration : iota(0U, 1U << num_rows)) {
                        // note that:
                        // next_cells_configuration for num_wayss includes the curr cell,
                        // but next_cells_configuration for next_num_wayss DOES NOT (and instead inclues (row, col+1))

                        if (num_wayss[next_cells_configuration] == 0) {
                            continue;
                        }

                        // for configurations where the curr cell is already covered
                        if (next_cells_configuration & (1U << row)) {
                            // (row, col) is already covered, add nothing
                            next_num_wayss[next_cells_configuration & ~(1U << row)] += num_wayss[next_cells_configuration];
                        }
                        // for configurations where the curr cell is not yet covered
                        else {
                            // can add a 1x2 tile, then update the resulting configuration
                            next_num_wayss[next_cells_configuration | (1U << row)] += num_wayss[next_cells_configuration];
                            if (row < num_rows - 1 && !(next_cells_configuration & (1U << (row + 1)))) {
                                // can add a 2x1 tile, then update the resulting configuration
                                next_num_wayss[next_cells_configuration | (1U << (row + 1))] += num_wayss[next_cells_configuration];
                            }
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
    // ans is num_ways where cells before (n-1, m-1) must be covered
    // and all the next cells (i.e. cells that are out-of-bound) are not covered
    std::cout << num_wayss[0] << '\n';
}