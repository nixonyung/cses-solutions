/*
ideas that won't work:
  - store a flag for all x to indicate if it has appeared
    => x <= 1e9 is too large
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
    auto numbers = std::vector<unsigned>(N);
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> numbers[i];
        }
        std::ranges::stable_sort(numbers);
    }

    unsigned num_unique_numbers = 1;
    {
        for (unsigned i = 1; i < N; i++) {
            if (numbers[i] != numbers[i - 1]) num_unique_numbers++;
        }
    }
    std::cout << num_unique_numbers << '\n';
}