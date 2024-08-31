#include <algorithm>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto n = int();
    std::cin >> n;

    auto ans = 0L;
    auto curr_max = 0;
    for (auto i = 0; i < n; i++) {
        auto x = int();
        std::cin >> x;

        curr_max = std::max(curr_max, x);
        ans += curr_max - x;
    }
    std::cout << ans << '\n';
}