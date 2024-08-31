#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto n = long();
    std::cin >> n;
    std::cout << n << ' ';

    while (n != 1) {
        n = (n & 1) ? (n * 3 + 1) : (n >> 1);
        std::cout << n << ' ';
    }
    std::cout << '\n';
}