#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    // hard-coded solutions for n <= 3
    if (N == 1) {
        std::cout << "1\n";
        return 0;
    }
    if (N == 2 || N == 3) {
        std::cout << "NO SOLUTION\n";
        return 0;
    }

    // enumerate even numbers increasingly, then enumerate odd numbers increasingly
    for (unsigned i = 2; i <= N; i += 2) {
        std::cout << i << ' ';
    }
    for (unsigned i = 1; i <= N; i += 2) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}