// (ref.) [Binary Exponentiation](https://cp-algorithms.com/algebra/binary-exp.html)

#include <iostream>

namespace {
const unsigned long MOD = 1e9 + 7;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    unsigned long num_bit_strings = 1;
    {
        unsigned long base = 2;
        for (; N > 0; N >>= 1) {
            if (N & 1) {
                num_bit_strings = (num_bit_strings * base) % MOD;
            }
            base = (base * base) % MOD;
        }
    }
    std::cout << num_bit_strings << '\n';
}