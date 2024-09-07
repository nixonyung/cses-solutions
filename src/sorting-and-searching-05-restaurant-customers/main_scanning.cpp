#include "utils.hpp"

int main() {
    enable_fast_io();

    /*
    implementations that won't work:
        - store counters for all a,b
            => a,b <= 1e9 is too large
    */

    auto n = read<uint>();

    auto starts = std::vector<uint>(n);
    auto ends = std::vector<uint>(n);
    {
        for (auto i : iota(0U, n)) {
            starts[i] = read<uint>();
            ends[i] = read<uint>();
        }
    }

    // direct implementation of the problem

    radix_sort(starts);
    radix_sort(ends);

    uint max_num_customers = 0;
    {
        uint start_idx = 0;
        uint end_idx = 0;
        uint curr_num_customers = 0;
        while (start_idx < n) {
            if (starts[start_idx] < ends[end_idx]) {
                curr_num_customers++;
                max_num_customers = std::max(max_num_customers, curr_num_customers);
                start_idx++;
            } else if (starts[start_idx] < ends[end_idx]) {
                curr_num_customers--;
                end_idx++;
            } else {
                start_idx++;
                end_idx++;
            }
        }
        // there maybe bs not yet processed, but they can be skipped
        // because processing them will only decrement curr_num and thus will not change ans
    }
    std::cout << max_num_customers << '\n';
}