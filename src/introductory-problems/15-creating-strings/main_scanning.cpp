#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace {
// hard-coded factorial results for n <= 8
const auto FACTORIALS = std::vector<unsigned>{1, 1, 2, 6, 24, 120, 720, 5040, 40320};
} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str;
    {
        std::cin >> str;
    }
    auto char_counter = std::vector<unsigned>(26, 0);
    {
        for (auto const &ch : str) {
            char_counter[ch - 'a']++;
        }
    }

    // (ref.) [Multinomial theorem - Interpretations](https://wikiwand.com/en/articles/Multinomial_theorem#Interpretations)
    unsigned num_total = FACTORIALS[str.size()];
    {
        for (auto const &count : char_counter) {
            num_total /= FACTORIALS[count];
        }
    }
    std::cout << num_total << '\n';

    // (ref.) [how can print only unique Permutations of a string?](https://stackoverflow.com/questions/67679226/how-can-print-only-unique-permutations-of-a-string)
    std::ranges::sort(str);
    do {
        std::cout << str << '\n';
    } while (std::ranges::next_permutation(str).found);
}
