#include <iostream>
#include <string>
#include <vector>

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
            char_counter[ch - 'A']++;
        }
    }
    char odd_char = 0;
    {
        for (char ch = 'A'; ch <= 'Z'; ch++) {
            if (char_counter[ch - 'A'] & 1) {
                // at most 1 character can appear odd number of times
                if (odd_char != 0) {
                    std::cout << "NO SOLUTION\n";
                    return 0;
                }
                odd_char = ch;
            }
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        for (unsigned i = 0; i < char_counter[ch - 'A'] / 2; i++) {
            std::cout << ch;
        }
    }
    // move the odd part to the center
    // following test outputs: move only a single character to the center
    if (odd_char != 0) {
        std::cout << odd_char;
    }
    for (char ch = 'Z'; ch >= 'A'; ch--) {
        for (unsigned i = 0; i < char_counter[ch - 'A'] / 2; i++) {
            std::cout << ch;
        }
    }
    std::cout << '\n';
}