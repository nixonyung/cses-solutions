// (ref.) [CSES Solutions - Missing Number](https://www.geeksforgeeks.org/missing-number-cses/)

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    auto sum = (unsigned long)N * (N + 1) / 2;
    {
        unsigned number;
        for (unsigned i = 0; i < N - 1; i++) {
            std::cin >> number;
            sum -= number;
        }
    }
    std::cout << sum << '\n';
}