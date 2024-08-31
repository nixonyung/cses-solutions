#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto s = std::string();
    std::cin >> s;

    auto char_counter = std::vector<int>(26, 0);
    for (auto const &ch : s) {
        char_counter[ch - 'A']++;
    }

    auto odd_char_idx = -1;
    for (auto i = 0; i < 26; i++) {
        if (char_counter[i] & 1) {
            // at most 1 character can appear odd number of times
            if (odd_char_idx != -1) {
                std::cout << "NO SOLUTION\n";
                return 0;
            }
            odd_char_idx = i;
        }
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < char_counter[i] / 2; j++) {
            std::cout << char('A' + i);
        }
    }
    // move the odd part to the center
    // following the tests: move only a single character to the center
    if (odd_char_idx != -1) {
        std::cout << char('A' + odd_char_idx);
    }
    for (int i = 25; i >= 0; i--) {
        for (int j = 0; j < char_counter[i] / 2; j++) {
            std::cout << char('A' + i);
        }
    }
    std::cout << '\n';
}