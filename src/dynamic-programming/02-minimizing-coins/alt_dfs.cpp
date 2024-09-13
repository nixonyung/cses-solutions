#include "utils.hpp"

namespace {
// (ref.) <https://cses.fi/problemset/hack/1634/entry/9878198/>
void dfs(
    uint &min_num_coins,                   // shared output
    uint curr_sum,                         // state
    uint const &target,                    // dependency
    std::vector<uint> const &coins_sorted, // dependency
    int coins_sorted_idx,                  // optimization: internal state to help finding the largest coin smaller than `target - curr_sum`
    uint curr_num_coins                    // internal state to calculate output
) {
    // update coins_sorted_idx
    {
        while (coins_sorted_idx >= 0 && coins_sorted[coins_sorted_idx] > target - curr_sum) {
            coins_sorted_idx--;
        }
        if (coins_sorted_idx < 0) {
            return;
        }
    }
    // take the minimum possible num_coins[curr_sum] if it is valid
    if ((target - curr_sum) % coins_sorted[coins_sorted_idx] == 0) {
        min_num_coins = std::min(min_num_coins, curr_num_coins + (target - curr_sum) / coins_sorted[coins_sorted_idx]);
        return;
    }
    // optimization: stop dfs if it is not possible to update min_num_coins
    if (
        curr_num_coins + 1 >= min_num_coins ||
        target / coins_sorted[coins_sorted_idx] >= min_num_coins
    ) {
        return;
    }
    for (auto i : iota(0, coins_sorted_idx + 1) | std::views::reverse) {
        dfs(min_num_coins, curr_sum + coins_sorted[i], target, coins_sorted, i, curr_num_coins + 1);
    }
}
} // namespace

int main() {
    enable_fast_io();

    auto n = read<uint>();
    auto target = read<uint>();
    auto coins_sorted = std::vector<uint>(n);
    {
        for (auto &coin : coins_sorted) {
            coin = read<uint>();
        }
        std::ranges::stable_sort(coins_sorted);
    }

    uint min_num_coins = std::numeric_limits<uint>::max();
    {
        dfs(min_num_coins,
            0,
            target,
            coins_sorted,
            n - 1,
            0);
    }
    std::cout << ((min_num_coins != std::numeric_limits<uint>::max()) ? (int)min_num_coins
                                                                      : -1)
              << '\n';
}