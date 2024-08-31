#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto t = int();
    std::cin >> t;

    while (t--) {
        auto a = int();
        auto b = int();
        std::cin >> a >> b;

        // as each move remove 3 coins, for cases where all coins can be removed,
        // the total number of coins must be a multiple of 3
        if ((a + b) % 3) {
            std::cout << "NO\n";
            continue;
        }
        // there exists a solution iff the size of the larger pile is at most twice the size of the smaller pile
        if ((a > b * 2) || (b > a * 2)) {
            std::cout << "NO\n";
            continue;
        }
        std::cout << "YES\n";
    }
}