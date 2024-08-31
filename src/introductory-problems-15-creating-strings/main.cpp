// TODO: [Algorithm to return all combinations of k elements from n](https://stackoverflow.com/questions/127704/algorithm-to-return-all-combinations-of-k-elements-from-n)

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    // hard-coded factorial results given n <= 8
    auto const factorial = std::vector<int>{1, 1, 2, 6, 24, 120, 720, 5040, 40320};

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto s = std::string();
    std::cin >> s;

    // (ref.) [Multinomial theorem - Interpretations](https://omni.wikiwand.com/en/articles/Multinomial_theorem#Interpretations)
    auto char_counter = std::vector<int>(26, 0);
    for (auto const &ch : s) {
        char_counter[ch - 'a']++;
    }
    auto num_total = factorial[s.size()];
    for (auto const &count : char_counter) {
        num_total /= factorial[count];
    }
    std::cout << num_total << '\n';

    // (ref.) [how can print only unique Permutations of a string?](https://stackoverflow.com/questions/67679226/how-can-print-only-unique-permutations-of-a-string)
    std::ranges::sort(s);
    do {
        std::cout << s << '\n';
    } while (std::ranges::next_permutation(s).found);
}
