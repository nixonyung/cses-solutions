#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto n = long();
    std::cin >> n;

    auto xorsum = 0;
    for (auto i = 1; i <= n; i++) {
        xorsum ^= i;
    }

    for (auto i = 0; i < n - 1; i++) {
        auto x = int();
        std::cin >> x;
        xorsum ^= x;
    }
    std::cout << xorsum << '\n';
}