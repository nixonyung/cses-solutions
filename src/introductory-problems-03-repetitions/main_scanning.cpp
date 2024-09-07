#include "utils.hpp"

int main() {
    enable_fast_io();

    auto s = read<string>();

    uint max_repeat_len = 0;
    {
        uint curr_repeat_len = 1;
        for (auto i : iota(1UL, s.size())) {
            if (s[i] == s[i - 1]) {
                curr_repeat_len++;
            } else {
                max_repeat_len = std::max(max_repeat_len, curr_repeat_len);
                curr_repeat_len = 1;
            }
        }
        max_repeat_len = std::max(max_repeat_len, curr_repeat_len);
    }
    std::cout << max_repeat_len << '\n';
}
