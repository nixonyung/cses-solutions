#include <iostream>

int main() {
    auto const MOD = int(1e9) + 7;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto n = int();
    std::cin >> n;

    // ans = 2^n
    // (ref.) [Binary Exponentiation](https://cp-algorithms.com/algebra/binary-exp.html)
    auto ans = 1L;
    auto step = 2L;
    while (n > 0) {
        if (n & 1) {
            ans = (ans * step) % MOD;
        }
        step = (step * step) % MOD;
        n >>= 1;
    }
    std::cout << ans << '\n';
}