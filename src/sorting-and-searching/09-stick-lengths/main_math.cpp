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

    auto numbers = std::vector<unsigned>(N);
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> numbers[i];
        }
        std::ranges::stable_sort(numbers);
    }
    // the target length is the median
    auto const target = numbers[numbers.size() >> 1];

    unsigned long costs_sum = 0;
    for (unsigned i = 0; i < N; i++) {
        costs_sum += (i < (numbers.size() >> 1)) ? target - numbers[i]
                                                 : numbers[i] - target;
    }
    std::cout << costs_sum << '\n';
}