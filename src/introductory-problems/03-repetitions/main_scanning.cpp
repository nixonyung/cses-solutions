#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str;
    {
        std::cin >> str;
    }

    unsigned max_repeat_len = 0;
    {
        decltype(max_repeat_len) repeat_len;
        for (unsigned i = 0; i < str.size(); i++) {
            repeat_len = (i != 0 && str[i] == str[i - 1]) ? repeat_len + 1 : 1;
            max_repeat_len = std::max(max_repeat_len, repeat_len);
        }
    }
    std::cout << max_repeat_len << '\n';
}
