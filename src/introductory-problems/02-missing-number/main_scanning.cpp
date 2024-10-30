// (ref.) [CSES Solutions - Missing Number](https://www.geeksforgeeks.org/missing-number-cses/)

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    unsigned xor_sum = 0;
    {
        for (unsigned i = 1; i <= N; i++) {
            xor_sum ^= i;
        }

        unsigned number;
        for (unsigned i = 0; i < N - 1; i++) {
            std::cin >> number;
            xor_sum ^= number;
        }
    }
    std::cout << xor_sum << '\n';
}