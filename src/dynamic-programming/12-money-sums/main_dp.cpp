#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }
    auto coins = std::vector<unsigned>(N);
    unsigned coins_sum = 0;
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> coins[i];
            coins_sum += coins[i];
        }
    }

    auto is_possibles = std::vector<bool>(coins_sum + 1, false);
    unsigned num_possibles = 0;
    {
        is_possibles[0] = true;

        for (auto const &coin : coins) {
            for (unsigned sum = coins_sum; sum >= coin; sum--) {
                if (!is_possibles[sum - coin] || is_possibles[sum]) continue;
                num_possibles++;
                is_possibles[sum] = true;
            }
        }
    }
    std::cout << num_possibles << '\n';
    for (unsigned i = 1; i <= coins_sum; i++) {
        if (is_possibles[i]) std::cout << i << ' ';
    }
    std::cout << '\n';
}