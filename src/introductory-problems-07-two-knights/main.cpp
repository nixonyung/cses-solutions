#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto n = int();
    std::cin >> n;

    // (ref.) [CSES Solutions - Two Knights](https://www.geeksforgeeks.org/cses-solutions-two-knights/)
    for (auto k = 1L; k <= n; k++) {
        // choose 2 cells from the board, order doesn't matter
        auto num_total = k * k * (k * k - 1) / 2;
        // 2 invalid configurations for each 2x3 and 3x2 cells
        auto num_invalid = (k - 1) * (k - 2) * 4;

        std::cout << num_total - num_invalid << '\n';
    }
}