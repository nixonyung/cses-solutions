#include "utils.hpp"

namespace {
struct Input {
    uint duration;
    uint deadline;
};
} // namespace

int main() {
    enable_fast_io();

    auto n = read<size_t>();

    auto inputs = std::vector<Input>(n);
    {
        for (auto &input : inputs) {
            input = {read<uint>(), read<uint>()};
        }
    }

    // (ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Sorting%20and%20Searching/Tasks%20and%20Deadlines.cpp>

    /*
    reward = sum_i{deadline_i - finish_time_i}
           = sum_i{deadline_i} - sum_i{finish_time_i}

    Note that deadlines are constants.

    Then we can simply get the maximum reward by minimizing the finishing times,
    i.e. always choose the task with the shortest duration first.
    */

    radix_sort(
        inputs,
        [](auto const &input) { return input.duration; }
    );

    long ans = 0;
    {
        long curr_time = 0;
        for (auto const &input : inputs) {
            curr_time += input.duration;
            ans += input.deadline - curr_time;
        }
    }
    std::cout << ans << '\n';
}