// (ref.) <https://cses.fi/problemset/hack/1634/entry/9878198/>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned TARGET;
    {
        std::cin >> N >> TARGET;
    }
    auto coins = std::vector<unsigned>(N);
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> coins[i];
        }
        std::ranges::stable_sort(coins);
    }

    unsigned min_num_coins = -1U;
    {
        auto dfs = [TARGET, &coins, &min_num_coins](
                       unsigned num_coins,
                       unsigned coin_idx,
                       unsigned target
                   ) {
            auto impl = [TARGET, &coins, &min_num_coins](
                            auto impl_ref,
                            unsigned num_coins,
                            unsigned coin_idx,
                            unsigned target
                        ) -> void {
                for (unsigned i = coin_idx; i <= coin_idx; i--) {
                    if (coins[i] > target) continue;
                    // if the largest coin at hand divides `target`, use it
                    if (target % coins[i] == 0) {
                        min_num_coins = std::min(min_num_coins, num_coins + target / coins[i]);
                        return;
                    }
                    // optimization: terminate if the largest coin at hand will never update min_num_coins
                    if (coins[i] * min_num_coins <= TARGET) return;
                    impl_ref(impl_ref, num_coins + 1, i, target - coins[i]);
                }
            };
            impl(impl, num_coins, coin_idx, target);
        };
        dfs(0, N - 1, TARGET);
    }
    std::cout << (int)min_num_coins << '\n';
}