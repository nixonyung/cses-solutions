#include <algorithm>
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
        std::ranges::stable_sort(coins); // worse time complexity but improves caching and branch prediction
    }

    auto min_num_coinss = std::vector<unsigned>(TARGET + 1, -1U);
    {
        min_num_coinss[0] = 0;

        for (unsigned target = 1; target <= TARGET; target++) {
            for (auto const &coin : coins) {
                if (coin > target || min_num_coinss[target - coin] == -1U) continue;
                min_num_coinss[target] = std::min(min_num_coinss[target], 1 + min_num_coinss[target - coin]);
            }
        }
    }
    std::cout << (int)min_num_coinss[TARGET] << '\n';
}