#include "utils.hpp"

namespace {
struct Input {
    uint start;
    uint end; // inclusive
    uint reward;
};
} // namespace

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto inputs = std::vector<Input>(n);
    {
        for (auto &input : inputs) {
            input = {read<uint>(), read<uint>(), read<uint>()};
        }
        // sort projects so that we can determine if an unconsidered project can be added to a set of projects simply by checking if input.start < "projects' largest `end`"
        std::ranges::stable_sort(
            inputs,
            {},
            UNARY_FN(input) { return input.end; }
        );
    }

    auto max_rewards = std::vector<ulong>(n); // max_reward for inputs[:i+1]
    {
        ulong prev_max_reward = 0;
        for (auto i : iota(0U, n)) {
            // want the largest input with input.end < inputs[i].start
            // by first finding the smallest input with input.end >= inputs[i].start
            auto it = std::ranges::lower_bound(
                inputs | std::views::take(i),
                inputs[i].start,
                {},
                UNARY_FN(input) { return input.end; }
            );
            auto input_idx = std::distance(inputs.begin(), it) - 1;
            if (0 <= input_idx && input_idx < i) {
                max_rewards[i] = std::max(prev_max_reward, max_rewards[input_idx] + inputs[i].reward);
            } else {
                max_rewards[i] = std::max(prev_max_reward, (ulong)inputs[i].reward);
            }
            prev_max_reward = max_rewards[i];
        }
    }
    std::cout << max_rewards[n - 1] << '\n';
}