#include "utils.hpp"

int main() {
    // hard-coded factorial results given n <= 8
    auto constexpr factorial = std::array<int, 9>{1, 1, 2, 6, 24, 120, 720, 5040, 40320};

    enable_fast_io();

    auto s = read<string>();

    auto char_counter = std::vector<uint>(26, 0);
    for (auto const &ch : s) {
        char_counter[ch - 'a']++;
    }

    // (ref.) [Multinomial theorem - Interpretations](https://omni.wikiwand.com/en/articles/Multinomial_theorem#Interpretations)
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
