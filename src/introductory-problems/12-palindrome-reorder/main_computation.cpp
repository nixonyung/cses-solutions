#include "utils.hpp"

int main() {
    enable_fast_io();

    auto s = read<string>();

    std::vector<uint> char_counter(26, 0);
    for (auto const &ch : s) {
        char_counter[ch - 'A']++;
    }

    char odd_char = 0;
    for (auto ch = 'A'; ch <= 'Z'; ch++) {
        if (char_counter[ch - 'A'] & 1) {
            // at most 1 character can appear odd number of times
            if (odd_char != 0) {
                std::cout << "NO SOLUTION\n";
                return 0;
            }
            odd_char = ch;
        }
    }

    for (auto ch = 'A'; ch <= 'Z'; ch++) {
        for (auto _ : iota(0U, char_counter[ch - 'A'] / 2)) {
            std::cout << ch;
        }
    }
    // move the odd part to the center
    // following the tests: move only a single character to the center
    if (odd_char != 0) {
        std::cout << odd_char;
    }
    for (auto ch = 'Z'; ch >= 'A'; ch--) {
        for (auto _ : iota(0U, char_counter[ch - 'A'] / 2)) {
            std::cout << ch;
        }
    }
    std::cout << '\n';
}