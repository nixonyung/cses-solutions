#include <algorithm>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto t = int();
    std::cin >> t;

    while (t--) {
        auto x = int();
        auto y = int();
        std::cin >> y >> x;

        auto layer_idx = long(std::max(x, y));
        if (layer_idx & 1) {
            // the largest element (layer_idx^2) is at top-right
            auto ans = layer_idx * layer_idx + (1 - y) + (x - layer_idx);
            std::cout << ans << '\n';
        } else {
            // the largest element (layer_idx^2) is at bottom-left
            auto ans = layer_idx * layer_idx + (y - layer_idx) + (1 - x);
            std::cout << ans << '\n';
        }
    }
}