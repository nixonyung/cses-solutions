// (ref.) [CSES - Sliding Median - Solution 1](https://usaco.guide/problems/cses-1076-sliding-median/solution#solution-1-maintaining-two-multisets)

#include <iostream>
#include <set>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned K;
    {
        std::cin >> N >> K;
    }

    auto numbers = std::vector<unsigned>(N);
    {
        auto numbers_lower = std::multiset<decltype(numbers)::value_type>(); // includes the median
        auto numbers_upper = std::multiset<decltype(numbers)::value_type>();
        {
            // put all numbers into `numbers_lower` (will also be sorted)
            for (unsigned i = 0; i < K; i++) {
                std::cin >> numbers[i];
                numbers_upper.insert(numbers[i]);
            }
            // move the later half of the numbers from `numbers_lower` to `numbers_upper`
            while (numbers_upper.size() > numbers_lower.size()) {
                numbers_lower.insert(numbers_lower.end(), *numbers_upper.begin());
                numbers_upper.erase(numbers_upper.begin());
            }
        }
        std::cout << *numbers_lower.rbegin() << ' ';
        {
            for (unsigned i = K; i < N; i++) {
                std::cin >> numbers[i];

                if (numbers[i - K] <= *(--numbers_lower.end())) {
                    // remove `numbers[i-K]` from `numbers_lower`
                    numbers_lower.extract(numbers[i - K]);
                    // add `numbers[i]` to `numbers_upper`
                    numbers_upper.insert(numbers[i]);
                    // transfer one number from `numbers_upper` to `numbers_lower`
                    numbers_lower.insert(numbers_lower.end(), *numbers_upper.begin());
                    numbers_upper.erase(numbers_upper.begin());
                } else {
                    // similar to the above
                    numbers_upper.extract(numbers[i - K]);
                    numbers_lower.insert(numbers[i]);
                    numbers_upper.insert(numbers_upper.begin(), *(--numbers_lower.end()));
                    numbers_lower.erase(--numbers_lower.end());
                }
                std::cout << *numbers_lower.rbegin() << ' ';
            }
        }
    }
    std::cout << '\n';
}