/*
Bbserve that given any set of coins with max_sum (i.e. the coins can create [1,max_sum]), and any coin not in the set:
  if coin <= max_sum+1:
    the set and x can create [1,max_sum+x]
  else: (i.e. coin > max_sum+1)
    There is no way to create max_sum+1.

greedy solution: try to pick the smallest `coin` while `coin <= max_sum+1`
*/

#include <algorithm>
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
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> coins[i];
        }
        std::ranges::stable_sort(coins);
    }

    unsigned long max_creatable_sum = 0;
    {
        for (auto const &coin : coins) {
            if (coin > max_creatable_sum + 1) break;
            max_creatable_sum += coin;
        }
    }
    std::cout << max_creatable_sum + 1 << '\n';
}