#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto s = std::string();
    std::cin >> s;

    auto ans = 1;
    auto curr_ch = s[0];
    auto curr_len = 1;
    for (auto i = 1; i < s.size(); i++) {
        if (s[i] == curr_ch) {
            curr_len++;
        } else {
            // lazily evaluate ans only when curr_ch changes
            ans = std::max(ans, curr_len);

            curr_ch = s[i];
            curr_len = 1;
        }
    }
    ans = std::max(ans, curr_len);
    std::cout << ans << '\n';
}
