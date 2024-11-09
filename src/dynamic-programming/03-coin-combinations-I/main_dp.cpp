#include <algorithm>
#include <iostream>
#include <vector>

namespace {
const unsigned long MOD = 1e9 + 7;
} // namespace

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
        std::ranges::stable_sort(coins); // worse time complexity but improves caching and branch prediction
    }

    auto num_combinationss = std::vector<unsigned long>(TARGET + 1, 0);
    {
        num_combinationss[0] = 1;

        for (unsigned target = 1; target <= TARGET; target++) {
            for (auto const &coin : coins) {
                if (coin > target) continue;
                num_combinationss[target] += num_combinationss[target - coin];
            }
            num_combinationss[target] %= MOD;
        }
    }
    std::cout << num_combinationss[TARGET] << '\n';
}