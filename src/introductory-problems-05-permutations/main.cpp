#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto n = int();
    std::cin >> n;

    // hard-coded solutions for n <= 3
    if (n == 1) {
        std::cout << "1\n";
        return 0;
    }
    if (n == 2 || n == 3) {
        std::cout << "NO SOLUTION\n";
        return 0;
    }

    // solution: enumerate even numbers increasingly, then enumerate odd numbers increasingly
    for (auto i = 2; i <= n; i += 2) {
        std::cout << i << ' ';
    }
    for (auto i = 1; i <= n; i += 2) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}